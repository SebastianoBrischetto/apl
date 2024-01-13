package rest_requests

import (
	"errors"
	"fmt"
	"golang/include/bot_communication"
	"golang/include/game_elements"
)

// rappresenta i possibili tipi di bot
type BotType int

const (
	RANDOM BotType = iota
	HUNT_AND_TARGET
	PARITY
	PROBABILITY
)

// ritorna i parametri necessari ad iniziare una partita contro il bot
func StartBotGame(gameData game_elements.GameData) (game_elements.Ocean, game_elements.Ocean, bot_communication.BotMoves, error) {
	// controlla che il bot sia supportato
	if err := checkBotType(BotType(gameData.Game_Code)); err != nil {
		return game_elements.Ocean{}, game_elements.Ocean{}, bot_communication.BotMoves{}, err
	}

	// crea l'oceano appartenente al giocatore e controlla che le navi piazzate al suo interno siano valide
	player_ocean := game_elements.NewOcean(gameData.Columns, gameData.Rows)
	for _, ship := range gameData.Ships {
		_, err := game_elements.NewShip(ship.Init_x, ship.Init_y, ship.Ship_type, ship.Direction, &player_ocean)
		if err != nil {
			return game_elements.Ocean{}, game_elements.Ocean{}, bot_communication.BotMoves{}, fmt.Errorf("nave non creata - %v", err)
		}
	}

	// recupera le mosse del bot
	botMoves, err := bot_communication.PlayAgainstBot("namedPipe", gameData)
	if err != nil {
		return game_elements.Ocean{}, game_elements.Ocean{}, bot_communication.BotMoves{}, fmt.Errorf("errore nel recuperare le mosse del bot - %v", err)
	}

	// inizializza l'ocean del bot (setta le celle occupate dalle navi del bot)
	bot_ocean := game_elements.NewOcean(gameData.Columns, gameData.Rows)
	for _, coord := range botMoves.OccupiedCoords {
		cell, _ := bot_ocean.GetCell(coord.X, coord.Y)
		cell.SetIsOccupied()
		bot_ocean.IncraseOccupiedUnhitCells(1)
	}
	return player_ocean, bot_ocean, botMoves, nil
}

// controlla se il bot appartiene a un tipo supportato
func checkBotType(bot_type BotType) error {
	switch bot_type {
	case RANDOM, HUNT_AND_TARGET, PARITY, PROBABILITY:
		return nil
	default:
		return errors.New("invalid bot type")
	}
}
