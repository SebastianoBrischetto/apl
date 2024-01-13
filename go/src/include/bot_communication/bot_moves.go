package bot_communication

import (
	"golang/include/game_elements"
)

// Azioni del bot (moves: celle da colpire, occupiedcoords: celle occupate dalle navi del bot)
type BotMoves struct {
	Moves          []game_elements.Coords `json:"moves"`
	OccupiedCoords []game_elements.Coords `json:"occupied_coords"`
}
