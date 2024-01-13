package game_elements

// parametri necessari per iniziare una griglia
type GameData struct {
	Game_Code int    `json:"game_code"`
	Columns   int    `json:"columns"`
	Rows      int    `json:"rows"`
	Ships     []Ship `json:"ships"`
}
