package rest_requests

import (
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

func checkBotType(game_code string) error {
	switch game_code {
	case "0":
		return nil
	case "1":
		return nil
	case "2":
		return nil
	case "3":
		return nil
	default:
		return fmt.Errorf("invalid bot value: %s", game_code)
	}
}

// ritorna i parametri necessari ad iniziare una partita contro il bot
func StartBotGame(gameData game_elements.GameData) (game_elements.Ocean, game_elements.Ocean, bot_communication.BotMoves, error) {
	err := checkBotType(gameData.Game_Code)
	if err != nil {
		return game_elements.Ocean{}, game_elements.Ocean{}, bot_communication.BotMoves{}, err
	}

	// crea l'oceano appartenente al giocatore
	player_ocean, err := start_player_ocean(gameData)
	if err != nil {
		return game_elements.Ocean{}, game_elements.Ocean{}, bot_communication.BotMoves{}, err
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
