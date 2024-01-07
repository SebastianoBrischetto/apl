package game_elements

import (
	"errors"
	"fmt"
)

// Ocean
type Ocean struct {
	columns              int
	rows                 int
	occupied_unhit_cells int
	cells                [][]*Cell
}

func NewOcean(columns, rows int) *Ocean {
	cells := make([][]*Cell, columns)
	for x := range cells {
		cells[x] = make([]*Cell, rows)
		for y := range cells[x] {
			cells[x][y] = NewCell()
		}
	}
	return &Ocean{
		columns:              columns,
		rows:                 rows,
		occupied_unhit_cells: 0,
		cells:                cells,
	}
}

func (o *Ocean) GetColumns() int {
	return o.columns
}

func (o *Ocean) GetRows() int {
	return o.rows
}

func (o *Ocean) GetCell(x, y int) (*Cell, error) {
	if x < 0 || x >= o.GetColumns() || y < 0 || y >= o.GetRows() {
		return nil, errors.New("out of bonds")
	}
	return o.cells[x][y], nil
}

func (o *Ocean) GetOccupiedUnhitCells() int {
	return o.occupied_unhit_cells
}

func (o *Ocean) IsSpaceOccupied(init_x, init_y, length int, direction Direction) error {
	for i := 0; i < length; i++ {
		cell, err := o.UpdateCoordinates(init_x, init_y, i, direction)
		if err != nil {
			return err
		} else if cell.is_occupied {
			return errors.New("not enough space")
		}
	}
	return nil
}

func (o *Ocean) Hit(x, y int) {
	cell, err := o.GetCell(x, y)
	if err != nil {
		fmt.Println("Error:", err)
		return
	}
	occupied, err := cell.SetIsHit()
	if err != nil {
		fmt.Println("Error:", err)
		return
	}
	if occupied {
		fmt.Println("Cell has been hit and is occupied")
		o.IncraseOccupiedUnhitCells(1)
	} else {
		fmt.Println("Cell has been hit and is not occupied")
	}
}

func (o *Ocean) IncraseOccupiedUnhitCells(n int) {
	o.occupied_unhit_cells += n
}

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
