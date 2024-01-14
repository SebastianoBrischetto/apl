// Pacchetto game_elements fornisce elementi di gioco per il server di battaglia navale.
package game_elements

import (
	"errors"
)

// Direction rappresenta le possibili direzioni di una nave.
type Direction int

const (
	UP Direction = iota
	RIGHT
	DOWN
	LEFT
)

// ShipType rappresenta i possibili tipi di nave.
type ShipType int

const (
	DESTROYER  ShipType = 2 ///< Nave di lunghezza 2.
	SUBMARINE  ShipType = 3 ///< Nave di lunghezza 3.
	CRUISER    ShipType = 1 ///< Nave di lunghezza 3.
	BATTLESHIP ShipType = 4 ///< Nave di lunghezza 4.
	CARRIER    ShipType = 5 ///< Nave di lunghezza 5.
)

// Ship rappresenta una nave con la sua posizione iniziale, tipo e direzione.
type Ship struct {
	InitX     int       `json:"init_x"`
	InitY     int       `json:"init_y"`
	ShipType  ShipType  `json:"ship_type"`
	Direction Direction `json:"direction"`
}

// checkShipType controlla se il tipo di nave appartiene a quelli supportati.
func checkShipType(ship_type ShipType) error {
	switch ship_type {
	case DESTROYER, SUBMARINE, CRUISER, BATTLESHIP, CARRIER:
		return nil
	default:
		return errors.New("tipo di nave non valido")
	}
}

// NewShip crea una nuova nave posizionata nell'oceano, verificando prima se lo spazio è disponibile.
// Restituisce un errore se il tipo di nave non è supportato o se lo spazio non è sufficiente.
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
	return &Ship{InitX: init_x, InitY: init_y, ShipType: ship_type, Direction: direction}, nil
}

// GetInitX restituisce la coordinata X della posizione iniziale della nave.
func (s *Ship) GetInitX() int {
	return s.InitX
}

// GetInitY restituisce la coordinata Y della posizione iniziale della nave.
func (s *Ship) GetInitY() int {
	return s.InitY
}

// GetShipType restituisce il tipo di nave.
func (s *Ship) GetShipType() ShipType {
	return s.ShipType
}

// GetDirection restituisce la direzione della nave.
func (s *Ship) GetDirection() Direction {
	return s.Direction
}
