package game_elements

// Struct to represent the game data
type GameData struct {
	Columns     int    `json:"columns"`
	Rows        int    `json:"rows"`
	Game_Type   string `json:"game_type"`
	Opponent_ID int    `json:"opponent_id"`
	Ships       []Ship `json:"ships"`
}
