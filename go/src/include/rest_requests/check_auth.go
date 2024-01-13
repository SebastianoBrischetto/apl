package rest_requests

import (
	"encoding/json"
	"errors"
	"io/ioutil"
	"net/http"
	"net/url"
	"time"
)

// effettua la richiesta al server di autenticazione e controlla che l'access token fornito dal client sia valido
func CheckAccessToken(username, access_token string) error {
	// inizializza un client http per effettuare la richiesta
	client := &http.Client{
		Timeout: time.Second * 10,
	}

	// setta i parametri della richiesta
	params := url.Values{}
	params.Set("username", username)

	// effettua la richiesta all'endpoint giusto del server di autenticazione
	resp, err := client.Get("http://auth_server:5000/api/get_token?" + params.Encode())
	if err != nil {
		return err
	}
	defer resp.Body.Close()

	// legge il body della risposta
	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		return err
	}

	// converte il body
	var accessToken AccessTokenResponse
	err = json.Unmarshal(body, &accessToken)
	if err != nil {
		return err
	}

	// controlla se l'access token ricevuto dal server di autenticazione coincide con quello fornito dall'utente
	if accessToken.AccessToken != access_token {
		return errors.New("access token invalido")
	}
	return nil
}
