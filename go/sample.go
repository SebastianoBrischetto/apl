package main

import (
	"errors"
	"fmt"
)

// Cell
type Cell struct {
	is_hit      bool
	is_occupied bool
}

func newCell() Cell {
	return Cell{}
}

func (c *Cell) hitCell() (bool, error) {
	if c.is_hit {
		return false, errors.New("Cell already hit")
	}
	c.is_hit = true
	if c.is_occupied {
		return true, nil
	}
	return false, nil
}

func (c *Cell) setIsOccupied() error {
	if c.is_occupied {
		return errors.New("Cell already occupied")
	}
	c.is_occupied = true
	return nil
}

// Ocean
type Ocean struct {
	columns int
	rows    int
	cells   [][]Cell
}

func newOcean(columns, rows int) *Ocean {
	cells := make([][]Cell, columns)
	for x := range cells {
		cells[x] = make([]Cell, rows)
		for y := range cells[x] {
			cells[x][y] = newCell()
		}
	}
	return &Ocean{
		columns: columns,
		rows:    rows,
		cells:   cells,
	}
}

func (o *Ocean) hit(x, y int) {
	occupied, err := o.cells[x][y].hitCell()
	if err != nil {
		fmt.Println("Error:", err)
	} else if occupied {
		fmt.Println("Cell is hit and occupied")
	} else {
		fmt.Println("Cell is hit and not occupied")
	}
}

// Main
func main() {
	ocean := newOcean(10, 10)
	// Accessing methods
	ocean.cells[9][9].setIsOccupied()
	ocean.hit(9, 9)
	ocean.hit(9, 9)
}
