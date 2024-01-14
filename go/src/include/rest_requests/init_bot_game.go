// Pacchetto rest_requests gestisce le richieste REST.
package rest_requests

import (
	"fmt"
	"golang/include/bot"
	"golang/include/game_elements"
)

// StartBotGame ritorna i parametri necessari per iniziare una partita contro il bot,
// inclusi l'oceano del bot e le mosse iniziali del bot.
func StartBotGame(game_data game_elements.GameData, creator string) (game_elements.Ocean, bot.BotMoves, error) {
	// Controlla il tipo di bot in base al codice della partita.
	err := checkBotType(game_data.GameCode)
	if err != nil {
		return game_elements.Ocean{}, bot.BotMoves{}, err
	}

	// Recupera le mosse del bot.
	bot_moves, err := bot.PlayAgainstBot(creator, game_data)
	if err != nil {
		return game_elements.Ocean{}, bot.BotMoves{}, fmt.Errorf("errore nel recuperare le mosse del bot - %v", err)
	}

	// Inizializza l'ocean del bot (imposta le celle occupate dalle navi del bot).
	bot_ocean := game_elements.NewOcean(game_data.Columns, game_data.Rows)
	for _, coord := range bot_moves.OccupiedCoords {
		cell, _ := bot_ocean.GetCell(coord.X, coord.Y)
		cell.SetIsOccupied()
		bot_ocean.IncraseOccupiedUnhitCells(1)
	}
	return bot_ocean, bot_moves, nil
}

// checkBotType controlla se il codice del gioco corrisponde a un tipo di bot valido.
func checkBotType(game_code string) error {
	switch game_code {
	case "0", "1", "2", "3":
		return nil
	default:
		return fmt.Errorf("tipo del bot non valido: %s", game_code)
	}
}
