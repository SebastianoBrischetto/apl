package rest_requests

import (
	"fmt"
	"net/http"
)

func StartGame(w http.ResponseWriter, r *http.Request) {
	game_init_data, err := handleInitGameJsonRequest(r)
	if err != nil {
		errorMessage := fmt.Sprintf("Error: %v", err)
		fmt.Println(errorMessage)
		http.Error(w, errorMessage, http.StatusBadRequest)
		return
	}
	err = CheckAccessToken(game_init_data.User, game_init_data.Access_Token)
	if err != nil {
		errorMessage := fmt.Sprintf("Error: %v", err)
		fmt.Println(errorMessage)
		http.Error(w, errorMessage, http.StatusBadRequest)
		return
	}
	done := make(chan bool)
	switch game_init_data.Game_Type {
	case "bot":
		go func() {
			defer func() {
				done <- true
			}()
			if err := StartBotGame(game_init_data.Game_Data); err != nil {
				errorMessage := fmt.Sprintf("Error: %v", err)
				fmt.Println(errorMessage)
				http.Error(w, errorMessage, http.StatusBadRequest)
			}
			//websocket
		}()
	case "player":
		// logica vs player
	default:
		fmt.Println("Modalita non supportata")
	}
	<-done
}

/*
func initWebSocketConnection(username, access_token string) {
	// Set up WebSocket connection
	u := url.URL{Scheme: "ws", Host: "localhost:5000", Path: "/ws"}
	conn, _, err := websocket.DefaultDialer.Dial(u.String(), nil)
	if err != nil {
		fmt.Println("WebSocket connection error:", err)
		return
	}
	defer conn.Close()

	//logica partita
}
*/
