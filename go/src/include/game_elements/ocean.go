package game_elements

import (
	"errors"
	"fmt"
)

// rappresenta una griglia di celle
type Ocean struct {
	Columns              int       `json:"columns,omitempty"`
	Rows                 int       `json:"rows,omitempty"`
	Occupied_unhit_cells int       `json:"occupied_unhit_cells,omitempty"`
	Cells                [][]*Cell `json:"cells,omitempty"`
}

// crea un nuovo oceano composto da columns*rows celle
func NewOcean(columns, rows int) Ocean {
	cells := make([][]*Cell, columns)
	for x := range cells {
		cells[x] = make([]*Cell, rows)
		for y := range cells[x] {
			cells[x][y] = NewCell()
		}
	}
	return Ocean{
		Columns:              columns,
		Rows:                 rows,
		Occupied_unhit_cells: 0,
		Cells:                cells,
	}
}

func (o *Ocean) GetColumns() int {
	return o.Columns
}

func (o *Ocean) GetRows() int {
	return o.Rows
}

// ritorna la cella con le coordinate x,y , se si prova ad accedere an una cella fuori dalla griglia viene tornato un errore
func (o *Ocean) GetCell(x, y int) (*Cell, error) {
	if x < 0 || x >= o.GetColumns() || y < 0 || y >= o.GetRows() {
		return nil, errors.New("out of bonds")
	}
	return o.Cells[x][y], nil
}

// ritorna il numero di celle occupate ma non ancora colpite
func (o *Ocean) GetOccupiedUnhitCells() int {
	return o.Occupied_unhit_cells
}

// indica se uno spazio della griglia risulta occupato
func (o *Ocean) IsSpaceOccupied(init_x, init_y, length int, direction Direction) error {
	for i := 0; i < length; i++ {
		cell, err := o.UpdateCoordinates(init_x, init_y, i, direction)
		if err != nil {
			return err
		} else if cell.GetIsOccupied() {
			return errors.New("not enough space")
		}
	}
	return nil
}

// colpisce una cella della griglia
func (o *Ocean) Hit(x, y int) (bool, error) {
	cell, err := o.GetCell(x, y)
	if err != nil {
		return false, err
	}
	occupied, err := cell.SetIsHit()
	if err != nil {
		return false, err
	}
	if occupied {
		fmt.Println("Cell has been hit and is occupied")
		o.IncraseOccupiedUnhitCells(-1)
		return true, nil
	} else {
		fmt.Println("Cell has been hit and is not occupied")
		return false, nil
	}
}

// aumenta/diminuisce il numero di celle colpite e occupate rimanenti
func (o *Ocean) IncraseOccupiedUnhitCells(n int) {
	o.Occupied_unhit_cells += n
}

// aggiorna le coordinate fornite per spostarsi verso una direzione
func (o *Ocean) UpdateCoordinates(x, y, increment int, direction Direction) (*Cell, error) {
	var return_x, return_y int
	switch direction {
	case UP:
		return_x = x
		return_y = y - increment
	case RIGHT:
		return_x = x + increment
		return_y = y
	case DOWN:
		return_x = x
		return_y = y + increment
	case LEFT:
		return_x = x - increment
		return_y = y
	default:
		return nil, errors.New("wrong direction")
	}
	cell, err := o.GetCell(return_x, return_y)
	if err != nil {
		return nil, err
	}
	return cell, nil
}
