// Pacchetto rest_requests gestisce le richieste REST.
package rest_requests

import (
	"encoding/json"
	"errors"
	"io/ioutil"
	"net/http"
	"net/url"
	"time"
)

// AccessTokenResponse rappresenta la risposta del server di autenticazione alla richiesta di un access token.
type AccessTokenResponse struct {
	AccessToken string `json:"access_token"`
}

// CheckAccessToken effettua la richiesta al server di autenticazione e verifica che l'access token fornito dal client sia valido.
// Restituisce un errore se l'access token è invalido o se si verifica un errore nella richiesta.
func CheckAccessToken(username, access_token string) error {
	// Inizializza un client http per effettuare la richiesta.
	client := &http.Client{
		Timeout: time.Second * 10,
	}

	// Imposta i parametri della richiesta.
	params := url.Values{}
	params.Set("username", username)

	// Effettua la richiesta all'endpoint del server di autenticazione.
	resp, err := client.Get("http://auth_server:5000/api/get_token?" + params.Encode())
	if err != nil {
		return err
	}
	defer resp.Body.Close()

	// Legge il corpo della risposta.
	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		return err
	}

	// Converte il corpo in una struttura AccessTokenResponse.
	var access_token_response AccessTokenResponse
	err = json.Unmarshal(body, &access_token_response)
	if err != nil {
		return err
	}

	// Verifica se l'access token ricevuto dal server di autenticazione coincide con quello fornito dall'utente.
	if access_token_response.AccessToken != access_token {
		return errors.New("access token invalido")
	}
	return nil
}
