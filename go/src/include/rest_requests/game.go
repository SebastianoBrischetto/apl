// Pacchetto rest_requests gestisce le richieste REST.
package rest_requests

import (
	"golang/include/bot"
	"golang/include/game_elements"
	"sync"
)

// Game rappresenta una partita in corso, con tutte le relative informazioni.
type Game struct {
	GameID   string                `json:"game_id,omitempty"`
	P1Ocean  *game_elements.Ocean  `json:"p1_ocean,omitempty"`
	P2Ocean  *game_elements.Ocean  `json:"p2_ocean,omitempty"`
	Moves    *bot.BotMoves         `json:"moves,omitempty"`
	P1Turn   bool                  `json:"p1_turn"`
	LastMove *game_elements.Coords `json:"last_move,omitempty"`
}

// Games contiene le informazioni sulle partite in corso, con accesso sincronizzato.
var (
	Games   = make(map[string]Game)
	GamesMu sync.RWMutex
)
