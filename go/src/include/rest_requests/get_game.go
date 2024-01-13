package rest_requests

import (
	"encoding/json"
	"net/http"
)

// recupera i dati di una partita in corso
func GetGame(w http.ResponseWriter, r *http.Request) {
	// recupera i parametri della richiesta
	game_id := r.URL.Query().Get("game_id")

	// blocca il mutex per la lettura
	gamesMu.RLock()
	defer gamesMu.RUnlock()

	// controlla che la partita esista
	game, exists := games[game_id]
	if !exists {
		http.Error(w, "Game not found", http.StatusNotFound)
		return
	}

	// converte i dati della partita in formato json
	response, err := json.Marshal(game)
	if err != nil {
		http.Error(w, "Error encoding JSON", http.StatusInternalServerError)
		return
	}

	w.Header().Set("Content-Type", "application/json")
	w.Write(response)
}
