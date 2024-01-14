package rest_requests

import (
	"fmt"
	"golang/include/game_elements"
)

func start_player_ocean(gameData game_elements.GameData) (game_elements.Ocean, error) {
	// crea l'oceano appartenente al giocatore e controlla che le navi piazzate al suo interno siano valide
	player_ocean := game_elements.NewOcean(gameData.Columns, gameData.Rows)
	for _, ship := range gameData.Ships {
		_, err := game_elements.NewShip(ship.Init_x, ship.Init_y, ship.Ship_type, ship.Direction, &player_ocean)
		if err != nil {
			return game_elements.Ocean{}, fmt.Errorf("nave non creata - %v", err)
		}
	}
	return player_ocean, nil
}
