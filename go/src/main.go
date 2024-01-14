package main

import (
	"fmt"
	"golang/include/rest_requests"
	"net/http"
)

func main() {
	// Imposta gli handler per le diverse route.
	http.HandleFunc("/start-game", rest_requests.StartGame)
	http.HandleFunc("/join-game", rest_requests.JoinGame)
	http.HandleFunc("/do-move", rest_requests.DoMove)
	http.HandleFunc("/get-game", rest_requests.GetGame)

	// Avvia il server sulla porta 8080.
	fmt.Println("Il server è in ascolto su :8080...")
	http.ListenAndServe(":8080", nil)
}
