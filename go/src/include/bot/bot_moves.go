// Pacchetto bot gestisce la comunicazione con il programma bot.
package bot

import (
	"golang/include/game_elements"
)

// BotMoves rappresenta le azioni del bot durante il gioco, includendo le celle da colpire (Moves) e le celle occupate dalle navi del bot (OccupiedCoords).
type BotMoves struct {
	Moves          []game_elements.Coords `json:"moves"`           // Elenco delle coordinate delle celle da colpire.
	OccupiedCoords []game_elements.Coords `json:"occupied_coords"` // Elenco delle coordinate delle celle occupate dalle navi del bot.
}
