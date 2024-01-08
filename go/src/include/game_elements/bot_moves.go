package game_elements

// Struct to represent the game data
type BotMoves struct {
	Moves          []Coords `json:"moves"`
	OccupiedCoords []Coords `json:"occupied_coords"`
}
