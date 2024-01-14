// Pacchetto rest_requests gestisce le richieste REST.
package rest_requests

import (
	"encoding/json"
	"net/http"
)

// GetGame recupera i dati di una partita in corso in base all'identificativo univoco della partita.
// Risponde con i dati della partita in formato JSON.
func GetGame(w http.ResponseWriter, r *http.Request) {
	// Recupera l'identificativo della partita dai parametri della richiesta.
	game_id := r.URL.Query().Get("game_id")

	// Controlla se la partita esiste.
	GamesMu.Lock()
	game, exists := Games[game_id]
	GamesMu.Unlock()
	if !exists {
		http.Error(w, "Partita non trovata", http.StatusNotFound)
		return
	}

	// Converte i dati della partita in formato JSON.
	response, err := json.Marshal(game)
	if err != nil {
		http.Error(w, "Errore durante la codifica JSON", http.StatusInternalServerError)
		return
	}

	// Imposta l'header della risposta e invia i dati della partita al client.
	w.Header().Set("Content-Type", "application/json")
	w.Write(response)
}
