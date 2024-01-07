package rest_requests

import (
	"errors"
	"fmt"
	"golang/go/src/include/bot_communication"
	"golang/go/src/include/game_elements"
)

type BotType int

const (
	RANDOM BotType = iota
	HUNT_AND_TARGET
	PARITY
	PROBABILITY
)

func StartBotGame(gameData game_elements.GameData) error {
	if err := checkBotType(BotType(gameData.Opponent_ID)); err != nil {
		return err
	}
	ocean := *game_elements.NewOcean(gameData.Columns, gameData.Rows)
	for _, ship := range gameData.Ships {
		_, err := game_elements.NewShip(ship.Init_x, ship.Init_y, ship.Ship_type, ship.Direction, &ocean)
		if err != nil {
			return fmt.Errorf("nave non creata - %v", err)
		}
	}
	botMoves, err := bot_communication.PlayAgainstBot("namedPipe", gameData)
	if err != nil {
		fmt.Println("Error in getting the bot moves :", err)
	}

	// TEST MOSSE BOT (da rimuovere)
	var turns int
	for i, move := range botMoves.Moves {
		ocean.Hit(move.X, move.Y)
		turns = i
	}
	fmt.Printf("unhit cells: %d , turns: %d \n", ocean.GetOccupiedUnhitCells(), turns)
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
