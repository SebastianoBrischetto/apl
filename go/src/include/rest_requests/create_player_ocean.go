// Pacchetto rest_requests gestisce le richieste REST.
package rest_requests

import (
	"fmt"
	"golang/include/game_elements"
)

// CreatePlayerOcean crea l'oceano appartenente al giocatore sulla base dei dati di gioco forniti.
// Verifica che le navi piazzate all'interno dell'oceano siano valide.
// Restituisce l'oceano del giocatore o un eventuale errore.
func CreatePlayerOcean(game_data game_elements.GameData) (game_elements.Ocean, error) {
	// Crea l'oceano appartenente al giocatore e controlla che le navi piazzate al suo interno siano valide.
	player_ocean := game_elements.NewOcean(game_data.Columns, game_data.Rows)
	for _, ship := range game_data.Ships {
		_, err := game_elements.NewShip(ship.InitX, ship.InitY, ship.ShipType, ship.Direction, &player_ocean)
		if err != nil {
			return game_elements.Ocean{}, fmt.Errorf("nave non creata - %v", err)
		}
	}
	return player_ocean, nil
}
