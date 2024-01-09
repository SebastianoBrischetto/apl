package game_elements

// Struct to represent the game data
type GameData struct {
	Game_Code int    `json:"game_code"`
	Columns   int    `json:"columns"`
	Rows      int    `json:"rows"`
	Ships     []Ship `json:"ships"`
}
