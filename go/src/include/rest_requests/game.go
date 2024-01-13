package rest_requests

import (
	"golang/include/bot_communication"
	"golang/include/game_elements"
	"sync"
)

// rappresenta una partita in corso
type Game struct {
	Game_id   string                      `json:"game_id,omitempty"`
	P1_ocean  *game_elements.Ocean        `json:"p1_ocean,omitempty"`
	P2_ocean  *game_elements.Ocean        `json:"p2_ocean,omitempty"`
	Moves     *bot_communication.BotMoves `json:"moves,omitempty"`
	P1_turn   bool                        `json:"p1_turn"`
	Last_move *game_elements.Coords       `json:"last_move,omitempty"`
}

// partite in corso
var (
	games   = make(map[string]Game)
	gamesMu sync.RWMutex
)
