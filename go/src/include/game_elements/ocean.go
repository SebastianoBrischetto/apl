// Pacchetto game_elements fornisce elementi di gioco per il server di battaglia navale.
package game_elements

import (
	"errors"
)

// Ocean rappresenta una griglia di celle in cui si svolge il gioco.
type Ocean struct {
	Columns            int       `json:"columns,omitempty"`
	Rows               int       `json:"rows,omitempty"`
	OccupiedUnhitCells int       `json:"occupied_unhit_cells,omitempty"`
	Cells              [][]*Cell `json:"cells,omitempty"`
}

// NewOcean restituisce un nuovo oceano con le dimensioni specificate, inizializzando le celle.
func NewOcean(columns, rows int) Ocean {
	cells := make([][]*Cell, columns)
	for x := range cells {
		cells[x] = make([]*Cell, rows)
		for y := range cells[x] {
			cells[x][y] = NewCell()
		}
	}
	return Ocean{
		Columns:            columns,
		Rows:               rows,
		OccupiedUnhitCells: 0,
		Cells:              cells,
	}
}

// GetColumns restituisce il numero di colonne della griglia dell'oceano.
func (o *Ocean) GetColumns() int {
	return o.Columns
}

// GetRows restituisce il numero di righe della griglia dell'oceano.
func (o *Ocean) GetRows() int {
	return o.Rows
}

// GetCell restituisce la cella alle coordinate specificate (x, y).
// Restituisce un errore se le coordinate sono fuori dai limiti della griglia.
func (o *Ocean) GetCell(x, y int) (*Cell, error) {
	if x < 0 || x >= o.GetColumns() || y < 0 || y >= o.GetRows() {
		return nil, errors.New("coordinate fuori dai limiti")
	}
	return o.Cells[x][y], nil
}

// GetOccupiedUnhitCells restituisce il numero di celle occupate ma non ancora colpite nell'oceano.
func (o *Ocean) GetOccupiedUnhitCells() int {
	return o.OccupiedUnhitCells
}

// IsSpaceOccupied verifica se uno spazio nella griglia dell'oceano è occupato a partire dalle coordinate specificate,
// in una determinata direzione, per una lunghezza specificata.
// Restituisce un errore se lo spazio non è sufficiente.
func (o *Ocean) IsSpaceOccupied(init_x, init_y, length int, direction Direction) error {
	for i := 0; i < length; i++ {
		cell, err := o.UpdateCoordinates(init_x, init_y, i, direction)
		if err != nil {
			return err
		} else if cell.GetIsOccupied() {
			return errors.New("spazio non sufficiente")
		}
	}
	return nil
}

// Hit colpisce la cella alle coordinate specificate (x, y) nella griglia dell'oceano.
// Restituisce true se la cella colpita era occupata o false altrimenti.
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
		o.IncraseOccupiedUnhitCells(-1)
		return true, nil
	} else {
		return false, nil
	}
}

// IncraseOccupiedUnhitCells aumenta o diminuisce il numero di celle occupate ma non ancora colpite.
func (o *Ocean) IncraseOccupiedUnhitCells(n int) {
	o.OccupiedUnhitCells += n
}

// UpdateCoordinates aggiorna le coordinate fornite per spostarsi in una direzione specifica,
// restituendo la cella risultante.
// Restituisce un errore se la direzione è errata o se le nuove coordinate sono fuori dai limiti della griglia.
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
		return nil, errors.New("direzione errata")
	}
	cell, err := o.GetCell(return_x, return_y)
	if err != nil {
		return nil, err
	}
	return cell, nil
}
