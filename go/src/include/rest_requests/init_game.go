package rest_requests

import (
	"encoding/json"
	"errors"
	"fmt"
	"golang/include/game_elements"
	"io/ioutil"
	"net/http"
)

// rappresenta i dati necessari per iniziare una partita
type GameInitData struct {
	User         string                 `json:"username"`
	Access_Token string                 `json:"access_token"`
	Game_Type    string                 `json:"game_type"`
	Game_Data    game_elements.GameData `json:"game_data"`
}

// inizia una partita
func StartGame(w http.ResponseWriter, r *http.Request) {
	// recupera i dati della richiesta
	game_init_data, err := handleInitGameJsonRequest(r)
	if err != nil {
		errorMessage := fmt.Sprintf("Error: %v", err)
		fmt.Println(errorMessage)
		http.Error(w, errorMessage, http.StatusBadRequest)
		return
	}

	// controlla che l'access token risulti valido
	/*
		err = CheckAccessToken(game_init_data.User, game_init_data.Access_Token)
		if err != nil {
			errorMessage := fmt.Sprintf("Error: %v", err)
			fmt.Println(errorMessage)
			http.Error(w, errorMessage, http.StatusBadRequest)
			return
		}
	*/

	// inizia la partita in base al tipo richiesto
	switch game_init_data.Game_Type {
	case "bot":
		// inizializza gli oceani dei due giocatori e recupera le mosse del bot
		p1_ocean, p2_ocean, bot_moves, err := StartBotGame(game_init_data.Game_Data)
		if err != nil {
			errorMessage := fmt.Sprintf("Error: %v", err)
			fmt.Println(errorMessage)
			http.Error(w, errorMessage, http.StatusBadRequest)
			return
		}

		// crea una partita con game_id = nome_utente
		game_id := game_init_data.User
		gamesMu.Lock()
		games[game_id] = Game{
			Game_id:  game_id,
			P1_ocean: &p1_ocean,
			P2_ocean: &p2_ocean,
			Moves:    &bot_moves,
			P1_turn:  true,
		}
		gamesMu.Unlock()
		return

	case "player":
		// logica vs player

	default:
		fmt.Println("Modalita non supportata")
	}
}

// gestisce il body della richiesta POST
func handleInitGameJsonRequest(r *http.Request) (*GameInitData, error) {
	if r.Method != http.MethodPost {
		return nil, errors.New("invalid request method")
	}

	body, err := ioutil.ReadAll(r.Body)
	if err != nil {
		return nil, errors.New("error reading request body")
	}

	var game_init_data GameInitData
	err = json.Unmarshal(body, &game_init_data)
	if err != nil {
		return nil, errors.New("error parsing JSON data")
	}
	return &game_init_data, nil
}
