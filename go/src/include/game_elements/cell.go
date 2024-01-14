// Pacchetto game_elements fornisce elementi di gioco per il server di battaglia navale.
package game_elements

import (
	"errors"
)

// Cell rappresenta una singola cella.
type Cell struct {
	IsHit      bool `json:"is_hit"`
	IsOccupied bool `json:"is_occupied"`
}

// NewCell restituisce una nuova istanza di Cell inizializzata con i valori predefiniti.
func NewCell() *Cell {
	return &Cell{IsHit: false, IsOccupied: false}
}

// SetIsHit imposta la cella come colpita e restituisce true se la cella era occupata.
// Restituisce un errore se la cella è già stata colpita in precedenza.
func (c *Cell) SetIsHit() (bool, error) {
	if c.GetIsHit() {
		return false, errors.New("cella già colpita")
	}
	c.IsHit = true
	if c.IsOccupied {
		return true, nil
	}
	return false, nil
}

// SetIsOccupied imposta la cella come occupata e restituisce un errore se la cella è già occupata.
func (c *Cell) SetIsOccupied() error {
	if c.GetIsOccupied() {
		return errors.New("cella già occupata")
	}
	c.IsOccupied = true
	return nil
}

// GetIsHit restituisce true se la cella è stata colpita, altrimenti restituisce false.
func (c *Cell) GetIsHit() bool {
	return c.IsHit
}

// GetIsOccupied restituisce true se la cella è occupata, altrimenti restituisce false.
func (c *Cell) GetIsOccupied() bool {
	return c.IsOccupied
}
