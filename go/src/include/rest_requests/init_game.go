package rest_requests

import (
	"encoding/json"
	"errors"
	"fmt"
	"golang/go/src/include/game_elements"
	"io/ioutil"
	"net/http"
)

func handleInitGameJsonRequest(r *http.Request) (*game_elements.GameData, error) {
	// Check if the request method is POST
	if r.Method != http.MethodPost {
		return nil, errors.New("invalid request method")
	}

	// Read the request body
	body, err := ioutil.ReadAll(r.Body)
	if err != nil {
		return nil, errors.New("error reading request body")
	}

	// Parse the JSON data into a struct
	var gameData game_elements.GameData
	err = json.Unmarshal(body, &gameData)
	if err != nil {
		return nil, errors.New("error parsing JSON data")
	}
	return &gameData, nil
}

func StartGame(w http.ResponseWriter, r *http.Request) {
	gameData, err := handleInitGameJsonRequest(r)
	if err != nil {
		errorMessage := fmt.Sprintf("Error: %v", err)
		fmt.Println(errorMessage)
		http.Error(w, errorMessage, http.StatusBadRequest)
		return
	}
	switch gameData.Game_Type {
	case "bot":
		if err := StartBotGame(*gameData); err != nil {
			errorMessage := fmt.Sprintf("Error: %v", err)
			fmt.Println(errorMessage)
			http.Error(w, errorMessage, http.StatusBadRequest)
		}
	case "player":
		// logica vs player
	default:
		fmt.Println("Modalita non supportata")
	}
}
