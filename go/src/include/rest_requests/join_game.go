// Pacchetto rest_requests gestisce le richieste REST.
package rest_requests

import (
	"fmt"
	"net/http"
)

// JoinGame permette a un giocatore di entrare in una partita.
func JoinGame(w http.ResponseWriter, r *http.Request) {
	// Recupera i dati della richiesta.
	new_game_data, err := HandleNewGameJsonRequests(r)
	if err != nil {
		error_message := fmt.Sprintf("Errore: %v", err)
		http.Error(w, error_message, http.StatusBadRequest)
		return
	}

	// Controlla che l'access token sia valido (commentato per ora).
	err = CheckAccessToken(new_game_data.User, new_game_data.AccessToken)
	if err != nil {
		error_message := fmt.Sprintf("Errore: %v", err)
		http.Error(w, error_message, http.StatusBadRequest)
		return
	}

	// Controlla che la modalità sia quella giusta.
	if new_game_data.GameType != "player" {
		error_message := "Errore: Modalità partita errata"
		http.Error(w, error_message, http.StatusBadRequest)
		return
	}
	game_id := new_game_data.GameData.GameCode

	// Controlla che la partita esista.
	GamesMu.Lock()
	game, exists := Games[game_id]
	GamesMu.Unlock()

	if !exists {
		http.Error(w, "Errore: Partita non trovata", http.StatusNotFound)
		return
	}

	// Controlla che non sia già presente un altro giocatore.
	if game.P2Ocean != nil {
		http.Error(w, "Errore: P2 già presente", http.StatusBadRequest)
		return
	}

	// Controlla la dimensione della griglia.
	if game.P1Ocean.Columns != new_game_data.GameData.Columns || game.P1Ocean.Rows != new_game_data.GameData.Rows {
		http.Error(w, "Errore: Dimensioni dell'oceano errate", http.StatusBadRequest)
		return
	}

	// Prova a creare l'oceano del giocatore P2.
	p2_ocean, err := CreatePlayerOcean(new_game_data.GameData)
	if err != nil {
		error_message := fmt.Sprintf("Errore: %v", err)
		http.Error(w, error_message, http.StatusBadRequest)
		return
	}
	// Aggiorna la partita con i dati del secondo giocatore.
	game.P2Ocean = &p2_ocean
	game.P2ID = new_game_data.User
	GamesMu.Lock()
	Games[game_id] = game
	GamesMu.Unlock()
}
