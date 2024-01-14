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

// GameInitData rappresenta i dati necessari per iniziare una partita.
type GameInitData struct {
	User        string                 `json:"username"`
	AccessToken string                 `json:"access_token"`
	GameType    string                 `json:"game_type"`
	GameData    game_elements.GameData `json:"game_data"`
}

// StartGame inizia una partita in base ai dati forniti nella richiesta.
func StartGame(w http.ResponseWriter, r *http.Request) {
	// Recupera i dati della richiesta.
	game_init_data, err := HandleNewGameJsonRequests(r)
	if err != nil {
		error_message := fmt.Sprintf("Errore: %v", err)
		http.Error(w, error_message, http.StatusBadRequest)
		return
	}

	// Controlla se l'access token è valido (commentato per ora).
	/*
		err = CheckAccessToken(game_init_data.User, game_init_data.Access_Token)
		if err != nil {
			error_message := fmt.Sprintf("Errore: %v", err)
			http.Error(w, error_message, http.StatusBadRequest)
			return
		}
	*/

	// Crea la griglia del giocatore che ha creato la partita.
	p1_ocean, err := CreatePlayerOcean(game_init_data.GameData)
	if err != nil {
		error_message := fmt.Sprintf("Errore: %v", err)
		http.Error(w, error_message, http.StatusBadRequest)
		return
	}

	// Inizia la partita in base al tipo richiesto.
	switch game_init_data.GameType {
	case "bot":
		// Inizializza gli oceani dei due giocatori e recupera le mosse del bot.
		bot_ocean, bot_moves, err := StartBotGame(game_init_data.GameData, game_init_data.User)
		if err != nil {
			error_message := fmt.Sprintf("Errore: %v", err)
			http.Error(w, error_message, http.StatusBadRequest)
			return
		}

		// Crea una partita con game_id = nome_utente.
		game_id := game_init_data.User
		GamesMu.Lock()
		Games[game_id] = Game{
			GameID:   game_id,
			P1Ocean:  &p1_ocean,
			P2Ocean:  &bot_ocean,
			Moves:    &bot_moves,
			P1Turn:   true,
			LastMove: nil,
		}
		GamesMu.Unlock()
		return

	case "player":
		// Crea una partita con game_id = nome_utente.
		game_id := game_init_data.User
		GamesMu.Lock()
		Games[game_id] = Game{
			GameID:   game_id,
			P1Ocean:  &p1_ocean,
			P2Ocean:  nil,
			Moves:    nil,
			P1Turn:   true,
			LastMove: nil,
		}
		GamesMu.Unlock()
		return

	default:
		fmt.Println("Modalità non supportata")
	}
}

// HandleNewGameJsonRequests gestisce il body della richiesta POST.
func HandleNewGameJsonRequests(r *http.Request) (*GameInitData, error) {
	if r.Method != http.MethodPost {
		return nil, errors.New("metodo di richiesta non valido")
	}

	body, err := ioutil.ReadAll(r.Body)
	if err != nil {
		return nil, errors.New("errore nella lettura del corpo della richiesta")
	}

	var new_game_data GameInitData
	err = json.Unmarshal(body, &new_game_data)
	if err != nil {
		return nil, errors.New("errore nel parsing dei dati JSON")
	}
	return &new_game_data, nil
}
