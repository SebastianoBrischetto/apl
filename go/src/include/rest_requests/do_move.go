package rest_requests

import (
	"encoding/json"
	"errors"
	"fmt"
	"golang/include/game_elements"
	"io/ioutil"
	"net/http"
)

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

	// blocca la mappa delle partite in corso e la chiude alla fine delle operazioni
	gamesMu.Lock()
	defer gamesMu.Unlock()

	// controlla che la partita esista
	game, exists := games[do_move_data.Game_id]
	if !exists {
		http.Error(w, "Game not found", http.StatusNotFound)
		return
	}

	// effettua il colpo
	err = game.P1_ocean.Hit(do_move_data.Coords.X, do_move_data.Coords.Y)
	if err != nil {
		errorMessage := fmt.Sprintf("Error: %v", err)
		fmt.Println(errorMessage)
		http.Error(w, errorMessage, http.StatusBadRequest)
		return
	}
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

// rappresenta la richiesta effettuata dal client
type DoMoveData struct {
	User         string               `json:"username"`
	Access_Token string               `json:"access_token"`
	Game_id      string               `json:"game_id"`
	Coords       game_elements.Coords `json:"coords"`
}
