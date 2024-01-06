package main

import (
	"errors"
	"fmt"
	"sync"

	"golang/go/bot_communication"
)

// Cell
type Cell struct {
	is_hit      bool
	is_occupied bool
}

func NewCell() *Cell {
	return &Cell{is_hit: false, is_occupied: false}
}

func (c *Cell) HitCell() (bool, error) {
	if c.is_hit {
		return false, errors.New("Cell already hit")
	}
	c.is_hit = true
	if c.is_occupied {
		return true, nil
	}
	return false, nil
}

func (c *Cell) SetIsOccupied() error {
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
	cells   [][]*Cell
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
		columns: columns,
		rows:    rows,
		cells:   cells,
	}
}

func (o *Ocean) Hit(x, y int) {
	occupied, err := o.cells[x][y].HitCell()
	if err != nil {
		fmt.Println("Error:", err)
		return
	}
	if occupied {
		fmt.Println("Cell has been hit and is occupied")
	} else {
		fmt.Println("Cell has been hit and is not occupied")
	}
}

func main() {
	var wg sync.WaitGroup
	wg.Add(1)
	go bot_communication.PlayAgainstBot(&wg, "pipeTest")
	wg.Wait()
}
