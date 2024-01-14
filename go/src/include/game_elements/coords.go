// Pacchetto game_elements fornisce elementi di gioco per il server di battaglia navale.
package game_elements

// Coords rappresenta le coordinate (X, Y) di una cella all'interno di un gioco.
type Coords struct {
	X int `json:"x"`
	Y int `json:"y"`
}
