package game_elements

// Struct to represent the game data
type GameInitData struct {
	User         string   `json:"username"`
	Access_Token string   `json:"access_token"`
	Game_Type    string   `json:"game_type"`
	Game_Data    GameData `json:"game_data"`
}
