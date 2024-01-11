package main

import (
	"fmt"
	"golang/include/rest_requests"
	"net/http"
)

func main() {
	http.HandleFunc("/start-game", rest_requests.StartGame)

	// Start the server on port 8080
	fmt.Println("Server is listening on :8080...")
	http.ListenAndServe(":8080", nil)
}
