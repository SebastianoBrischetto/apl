// Pacchetto rest_requests gestisce le richieste REST.
package rest_requests

import (
	"fmt"
	"net/http"
	"net/url"
	"time"
)

// DeleteGame elimina la partita indicata.
func UpdateScore(p1_username, p2_username string, p1_won bool) error {
	// Inizializza un client http per effettuare la richiesta.
	client := &http.Client{
		Timeout: time.Second * 10,
	}
	// Imposta i parametri della richiesta.
	params := url.Values{}
	params.Set("p1_username", p1_username)
	params.Set("p2_username", p2_username)
	params.Set("p1_won", fmt.Sprintf("%t", p1_won))

	resp, err := client.Head("http://auth_server:5000/api/update_elo?" + params.Encode())
	if err != nil {
		return err
	}
	defer resp.Body.Close()

	// Check the HTTP status code.
	if resp.StatusCode != http.StatusOK {
		// Handle non-OK status code as needed.
		return fmt.Errorf("unexpected status code: %d", resp.StatusCode)
	}
	return nil
}
