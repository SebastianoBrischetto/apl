// Pacchetto game_elements fornisce elementi di gioco per il server di battaglia navale.
package game_elements

// GameData rappresenta i parametri necessari per iniziare una griglia di gioco.
type GameData struct {
	GameCode string `json:"game_code"`
	Columns  int    `json:"columns"`
	Rows     int    `json:"rows"`
	Ships    []Ship `json:"ships"`
}
