package game_elements

import (
	"errors"
)

type Direction int

const (
	UP Direction = iota
	RIGHT
	DOWN
	LEFT
)

type ShipType int

const (
	DESTROYER  ShipType = 2 ///< Nave di lunghezza 2.
	SUBMARINE  ShipType = 3 ///< Nave di lunghezza 3.
	CRUISER    ShipType = 1 ///< Nave di lunghezza 3.
	BATTLESHIP ShipType = 4 ///< Nave di lunghezza 4.
	CARRIER    ShipType = 5 ///< Nave di lunghezza 5.
)

type Ship struct {
	Init_x    int       `json:"init_x"`
	Init_y    int       `json:"init_y"`
	Ship_type ShipType  `json:"ship_type"`
	Direction Direction `json:"direction"`
}

func checkShipType(ship_type ShipType) error {
	switch ship_type {
	case DESTROYER, SUBMARINE, CRUISER, BATTLESHIP, CARRIER:
		return nil
	default:
		return errors.New("invalid ship type")
	}
}

func NewShip(init_x, init_y int, ship_type ShipType, direction Direction, ocean *Ocean) (*Ship, error) {
	if err := checkShipType(ship_type); err != nil {
		return nil, err
	}
	length := int(ship_type)
	if ship_type == CRUISER {
		length = 3
	}
	if err := ocean.IsSpaceOccupied(init_x, init_y, length, direction); err != nil {
		return nil, err
	}
	for i := 0; i < length; i++ {
		cell, _ := ocean.UpdateCoordinates(init_x, init_y, i, direction)
		cell.SetIsOccupied()
	}
	ocean.IncraseOccupiedUnhitCells(length)
	return &Ship{Init_x: init_x, Init_y: init_y, Ship_type: ship_type, Direction: direction}, nil
}

func (s *Ship) GetInitX() int {
	return s.Init_x
}
func (s *Ship) GetInitY() int {
	return s.Init_y
}
func (s *Ship) GetShipType() ShipType {
	return s.Ship_type
}
func (s *Ship) GetDirection() Direction {
	return s.Direction
}
