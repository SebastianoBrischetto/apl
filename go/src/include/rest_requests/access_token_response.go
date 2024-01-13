package rest_requests

// rappresenta la risposta del server di autenticazione alla richiesta di un access token
type AccessTokenResponse struct {
	AccessToken string `json:"access_token"`
}
