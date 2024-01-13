package main

import (
	"fmt"
	"golang/include/rest_requests"
	"net/http"
)

func main() {
	http.HandleFunc("/start-game", rest_requests.StartGame)
	http.HandleFunc("/do-move", rest_requests.DoMove)
	http.HandleFunc("/get-game", rest_requests.GetGame)

	fmt.Println("Server is listening on :8080...")
	http.ListenAndServe(":8080", nil)
}
