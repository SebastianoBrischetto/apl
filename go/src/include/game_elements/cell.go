package game_elements

import (
	"errors"
)

// Cell
type Cell struct {
	is_hit      bool
	is_occupied bool
}

func NewCell() *Cell {
	return &Cell{is_hit: false, is_occupied: false}
}

func (c *Cell) SetIsHit() (bool, error) {
	if c.GetIsHit() {
		return false, errors.New("Cell already hit")
	}
	c.is_hit = true
	if c.is_occupied {
		return true, nil
	}
	return false, nil
}

func (c *Cell) SetIsOccupied() error {
	if c.GetIsOccupied() {
		return errors.New("Cell already occupied")
	}
	c.is_occupied = true
	return nil
}

func (c *Cell) GetIsHit() bool {
	return c.is_hit
}

func (c *Cell) GetIsOccupied() bool {
	return c.is_occupied
}
