package rest_requests

import (
	"errors"
	"fmt"
	"golang/include/bot_communication"
	"golang/include/game_elements"
)

type BotType int

const (
	RANDOM BotType = iota
	HUNT_AND_TARGET
	PARITY
	PROBABILITY
)

func StartBotGame(gameData game_elements.GameData) error {
	if err := checkBotType(BotType(gameData.Game_Code)); err != nil {
		return err
	}
	player_ocean := game_elements.NewOcean(gameData.Columns, gameData.Rows)
	for _, ship := range gameData.Ships {
		_, err := game_elements.NewShip(ship.Init_x, ship.Init_y, ship.Ship_type, ship.Direction, player_ocean)
		if err != nil {
			return fmt.Errorf("nave non creata - %v", err)
		}
	}
	botMoves, err := bot_communication.PlayAgainstBot("namedPipe", gameData)
	if err != nil {
		return fmt.Errorf("errore nel recuperare le mosse del bot - %v", err)
	}
	bot_ocean := game_elements.NewOcean(gameData.Columns, gameData.Rows)
	for _, coord := range botMoves.OccupiedCoords {
		cell, _ := bot_ocean.GetCell(coord.X, coord.Y)
		cell.SetIsOccupied()
		bot_ocean.IncraseOccupiedUnhitCells(1)
	}
	fmt.Println("Mosse del bot: ", botMoves.Moves)
	fmt.Println("Celle del bot: ", botMoves.OccupiedCoords)
	return nil
}

func checkBotType(bot_type BotType) error {
	switch bot_type {
	case RANDOM, HUNT_AND_TARGET, PARITY, PROBABILITY:
		return nil
	default:
		return errors.New("invalid bot type")
	}
}
