// Pacchetto rest_requests gestisce le richieste REST.
package rest_requests

import (
	"encoding/json"
	"errors"
	"fmt"
	"golang/include/game_elements"
	"io/ioutil"
	"net/http"
)

// DoMoveData rappresenta la richiesta effettuata dal client per eseguire un colpo.
type DoMoveData struct {
	User        string               `json:"username"`
	AccessToken string               `json:"access_token"`
	GameID      string               `json:"game_id"`
	Coords      game_elements.Coords `json:"coords"`
}

// GameOverResponse rappresenta la risposta in caso di partita terminata
type GameOverResponse struct {
	LastMove *game_elements.Coords `json:"last_move"`
	P1Won    bool                  `json:"p1_won"`
}

// GameOverResponse rappresenta la risposta in caso di colpo valido
type DoMoveResponse struct {
	LastMove   *game_elements.Coords `json:"last_move,omitempty"`
	IsOccupied bool                  `json:"is_occupied"`
}

// IsGameOver controlla se la partita è finita e ritorna la risposta da inviare.
func IsGameOver(game Game) (interface{}, bool) {
	if game.P1Ocean.IsFleetDestroyed() || game.P2Ocean.IsFleetDestroyed() {
		return GameOverResponse{
			LastMove: game.LastMove,
			P1Won:    game.P2Ocean.IsFleetDestroyed(),
		}, true
	}
	return GameOverResponse{}, false
}

// DoMove effettua un colpo alle coordinate fornite sulla griglia dell'avversario.
// Risponde con l'esito del colpo ed eventuali informazioni aggiuntive.
func DoMove(w http.ResponseWriter, r *http.Request) {
	// Recupera i dati della richiesta dal corpo della richiesta JSON.
	do_move_data, err := handleDoMoveJsonRequest(r)
	if err != nil {
		error_message := fmt.Sprintf("Errore: %v", err)
		http.Error(w, error_message, http.StatusBadRequest)
		return
	}

	// Controlla che l'access token sia valido (commentato per ora).
	/*
		err = CheckAccessToken(do_move_data.User, do_move_data.Access_Token)
		if err != nil {
			error_message := fmt.Sprintf("Errore: %v", err)
			http.Error(w, error_message, http.StatusBadRequest)
			return
		}
	*/

	game_id := do_move_data.GameID

	// Controlla se la partita esiste.
	GamesMu.Lock()
	game, exists := Games[game_id]
	GamesMu.Unlock()

	// Se la partita non esiste, restituisce un errore 404.
	if !exists {
		http.Error(w, "Errore: partita non trovata", http.StatusNotFound)
		return
	}

	// Se manca l'oceano del giocatore P2, restituisce un errore 404.
	if game.P2Ocean == nil {
		http.Error(w, "Errore: P2 mancante", http.StatusNotFound)
		return
	}

	// Controlla se e il turno del giocatore.
	is_p1 := (do_move_data.User == game_id)
	p1_turn := game.P1Turn
	if p1_turn != is_p1 {
		error_message := "Errore: turno nemico"
		fmt.Println(error_message)
		http.Error(w, error_message, http.StatusBadRequest)
		return
	}

	// Se la partita e finita lo comunica al perdente ed elimina la partita dalla memoria
	response, is_game_over := IsGameOver(game)
	if is_game_over {
		w.Header().Set("Content-Type", "application/json")
		json.NewEncoder(w).Encode(response)
		GamesMu.Lock()
		delete(Games, game_id)
		GamesMu.Unlock()
		return
	}

	// Recupera l'oceano da colpire in base al turno.
	var ocean *game_elements.Ocean
	if is_p1 {
		ocean = game.P2Ocean
	} else {
		ocean = game.P1Ocean
	}

	// Esegue il colpo alle coordinate fornite (se valide).
	x := do_move_data.Coords.X
	y := do_move_data.Coords.Y
	is_occupied, err := ocean.Hit(x, y)
	if err != nil {
		errorMessage := fmt.Sprintf("Errore: %v", err)
		fmt.Println(errorMessage)
		http.Error(w, errorMessage, http.StatusBadRequest)
		return
	}

	// Risponde al client informandolo della vittoria o con l'esito del colpo e le informazioni aggiuntive.
	response, is_game_over = IsGameOver(game)
	if !is_game_over {
		response = DoMoveResponse{
			LastMove:   game.LastMove,
			IsOccupied: is_occupied,
		}
	}
	w.Header().Set("Content-Type", "application/json")
	json.NewEncoder(w).Encode(response)

	// Esegue la mossa del bot o passa il turno all'altro giocatore.
	if game.Moves != nil {
		// Se la partita e finita la elimina
		if is_game_over {
			GamesMu.Lock()
			delete(Games, game_id)
			GamesMu.Unlock()
			return
		}
		moves := game.Moves.Moves
		x = moves[0].X
		y = moves[0].Y
		game.P1Ocean.Hit(x, y)
		game.Moves.Moves = moves[1:]
	} else {
		game.P1Turn = !p1_turn
	}

	// Aggiorna lo stato della partita.
	game.LastMove = &game_elements.Coords{X: x, Y: y}
	GamesMu.Lock()
	Games[game_id] = game
	GamesMu.Unlock()
}

// handleDoMoveJsonRequest gestisce il corpo della richiesta POST e restituisce i dati della richiesta.
func handleDoMoveJsonRequest(r *http.Request) (*DoMoveData, error) {
	if r.Method != http.MethodPost {
		return nil, errors.New("metodo non valido")
	}

	body, err := ioutil.ReadAll(r.Body)
	if err != nil {
		return nil, errors.New("errore durante la lettura del corpo della richiesta")
	}

	var do_move_data DoMoveData
	err = json.Unmarshal(body, &do_move_data)
	if err != nil {
		return nil, errors.New("errore durante il parsing dei dati JSON")
	}
	return &do_move_data, nil
}
