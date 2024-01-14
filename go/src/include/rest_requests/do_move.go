package rest_requests

import (
	"encoding/json"
	"errors"
	"fmt"
	"golang/include/game_elements"
	"io/ioutil"
	"net/http"
)

// rappresenta la richiesta effettuata dal client
type DoMoveData struct {
	User         string               `json:"username"`
	Access_Token string               `json:"access_token"`
	Game_id      string               `json:"game_id"`
	Coords       game_elements.Coords `json:"coords"`
}

// effettua un hit alle coordinate fornite
func DoMove(w http.ResponseWriter, r *http.Request) {
	// recupera i dati della richiesta
	do_move_data, err := handleDoMoveJsonRequest(r)
	if err != nil {
		errorMessage := fmt.Sprintf("Error: %v", err)
		fmt.Println(errorMessage)
		http.Error(w, errorMessage, http.StatusBadRequest)
		return
	}

	// controlla che l'access token sia valido
	/*
		err = CheckAccessToken(do_move_data.User, do_move_data.Access_Token)
		if err != nil {
			errorMessage := fmt.Sprintf("Error: %v", err)
			fmt.Println(errorMessage)
			http.Error(w, errorMessage, http.StatusBadRequest)
			return
		}
	*/

	game_id := do_move_data.Game_id

	// controlla che la partita esista
	gamesMu.Lock()
	game, exists := games[game_id]
	gamesMu.Unlock()

	// se la partita non esiste esce
	if !exists {
		http.Error(w, "Game not found", http.StatusNotFound)
		return
	}

	// se manca l'oceano del giocatore p2 esce
	if game.P2_ocean == nil {
		http.Error(w, "P2 missing", http.StatusNotFound)
		return
	}

	// controlla il turno
	is_p1 := (do_move_data.User == game_id)
	p1_turn := game.P1_turn
	if p1_turn != is_p1 {
		errorMessage := "errore: turno nemico"
		fmt.Println(errorMessage)
		http.Error(w, errorMessage, http.StatusBadRequest)
		return
	}

	// recupera l'oceano da colpire
	var ocean *game_elements.Ocean
	if is_p1 {
		ocean = game.P2_ocean
	} else {
		ocean = game.P1_ocean
	}

	// effettua il colpo (se valido)
	x := do_move_data.Coords.X
	y := do_move_data.Coords.Y
	is_occupied, err := ocean.Hit(x, y)
	if err != nil {
		errorMessage := fmt.Sprintf("Error: %v", err)
		fmt.Println(errorMessage)
		http.Error(w, errorMessage, http.StatusBadRequest)
		return
	}

	// risponde al client
	response := struct {
		Last_move  *game_elements.Coords `json:"last_move,omitempty"`
		IsOccupied bool                  `json:"is_occupied"`
	}{
		Last_move:  game.Last_move,
		IsOccupied: is_occupied,
	}
	w.Header().Set("Content-Type", "application/json")
	json.NewEncoder(w).Encode(response)

	// esegue la mossa del bot o passa il turno all'altro giocatore
	if game.Moves != nil {
		moves := game.Moves.Moves
		x = moves[0].X
		y = moves[0].Y
		game.P1_ocean.Hit(x, y)
		game.Moves.Moves = moves[1:]
	} else {
		game.P1_turn = !p1_turn
	}

	// aggiorna lo stato della partita
	game.Last_move = &game_elements.Coords{X: x, Y: y}
	gamesMu.Lock()
	games[game_id] = game
	gamesMu.Unlock()

}

// gestisce il body della richiesta POST
func handleDoMoveJsonRequest(r *http.Request) (*DoMoveData, error) {
	if r.Method != http.MethodPost {
		return nil, errors.New("invalid request method")
	}

	body, err := ioutil.ReadAll(r.Body)
	if err != nil {
		return nil, errors.New("error reading request body")
	}

	var DoMoveData DoMoveData
	err = json.Unmarshal(body, &DoMoveData)
	if err != nil {
		return nil, errors.New("error parsing JSON data")
	}
	return &DoMoveData, nil
}
