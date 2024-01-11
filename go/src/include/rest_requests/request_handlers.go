package rest_requests

import (
	"encoding/json"
	"errors"
	"golang/include/game_elements"
	"io/ioutil"
	"net/http"
	"net/url"
	"time"
)

func handleInitGameJsonRequest(r *http.Request) (*game_elements.GameInitData, error) {
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
	var game_init_data game_elements.GameInitData
	err = json.Unmarshal(body, &game_init_data)
	if err != nil {
		return nil, errors.New("error parsing JSON data")
	}
	return &game_init_data, nil
}

func CheckAccessToken(username, access_token string) error {
	client := &http.Client{
		Timeout: time.Second * 10,
	}

	params := url.Values{}
	params.Set("username", username)

	resp, err := client.Get("http://auth_server:5000/api/get_token?" + params.Encode())
	if err != nil {
		return err
	}
	defer resp.Body.Close()

	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		return err
	}

	var accessToken AccessTokenResponse
	err = json.Unmarshal(body, &accessToken)
	if err != nil {
		return err
	}

	// Check if the returned access token matches the expected one
	if accessToken.AccessToken != access_token {
		return errors.New("access token invalido")
	}
	return nil
}
