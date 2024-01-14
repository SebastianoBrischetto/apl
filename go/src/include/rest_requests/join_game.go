package rest_requests

import (
	"fmt"
	"net/http"
)

// inizia una partita
func JoinGame(w http.ResponseWriter, r *http.Request) {
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

	// controlla che la modalita sia quella giusta
	if game_init_data.Game_Type != "player" {
		errorMessage := "Error: Modalita partita errata"
		fmt.Println(errorMessage)
		http.Error(w, errorMessage, http.StatusBadRequest)
		return
	}
	game_id := game_init_data.Game_Data.Game_Code

	// controlla che la partita esista
	gamesMu.Lock()
	game, exists := games[game_id]
	gamesMu.Unlock()

	if !exists {
		http.Error(w, "Game not found", http.StatusNotFound)
		return
	}

	// controlla che non sia gia presente un altro giocatore
	if game.P2_ocean != nil {
		http.Error(w, "P2 already present", http.StatusBadRequest)
		return
	}

	// controlla la dimensione della griglia
	if game.P1_ocean.Columns != game_init_data.Game_Data.Columns || game.P1_ocean.Rows != game_init_data.Game_Data.Rows {
		http.Error(w, "Wrong ocean size", http.StatusBadRequest)
		return
	}

	// prova a creare l'oceano del giocatore p2
	p2_ocean, err := start_player_ocean(game_init_data.Game_Data)
	if err != nil {
		errorMessage := fmt.Sprintf("Error: %v", err)
		fmt.Println(errorMessage)
		http.Error(w, errorMessage, http.StatusBadRequest)
		return
	}
	// aggiorna la partita con i dati del secondo giocatore
	game.P2_ocean = &p2_ocean
	gamesMu.Lock()
	games[game_id] = game
	gamesMu.Unlock()
}
