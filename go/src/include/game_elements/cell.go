package game_elements

import (
	"errors"
)

// rappresenta la cella
type Cell struct {
	Is_hit      bool `json:"is_hit"`
	Is_occupied bool `json:"is_occupied"`
}

// crea una nuova cella
func NewCell() *Cell {
	return &Cell{Is_hit: false, Is_occupied: false}
}

// setta la cella a colpita (se gia colpita torna un errore), torna true se ha colpito una cella occupata
func (c *Cell) SetIsHit() (bool, error) {
	if c.GetIsHit() {
		return false, errors.New("Cell already hit")
	}
	c.Is_hit = true
	if c.Is_occupied {
		return true, nil
	}
	return false, nil
}

// setta la cella a occupata (se gia occupata torna un errore)
func (c *Cell) SetIsOccupied() error {
	if c.GetIsOccupied() {
		return errors.New("Cell already occupied")
	}
	c.Is_occupied = true
	return nil
}

func (c *Cell) GetIsHit() bool {
	return c.Is_hit
}

func (c *Cell) GetIsOccupied() bool {
	return c.Is_occupied
}
