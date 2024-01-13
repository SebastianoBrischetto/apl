package bot_communication

import (
	"bufio"
	"fmt"
	"os"
	"syscall"
)

// rappresenta il canale di comunicazione.
type Communication struct {
	pipe_name string
	pipe      *os.File
	scanner   *bufio.Scanner
}

// esegue il setup per l'ipc
func EstablishCommunication(pipeName string) (*Communication, error) {
	// crea la named pipe
	CreateNamedPipe(pipeName)

	// apre la named pipe per leggere
	pipe, err := os.OpenFile(pipeName, os.O_RDWR, os.ModeNamedPipe)
	if err != nil {
		return nil, fmt.Errorf("error opening file for reading: %v", err)
	}

	// inizializza lo scanner
	scanner := bufio.NewScanner(pipe)

	return &Communication{pipe_name: pipeName, pipe: pipe, scanner: scanner}, nil
}

// crea la named pipe (la rimuove se gia esistente).
func CreateNamedPipe(pipeName string) {
	os.Remove(pipeName)
	if err := syscall.Mkfifo(pipeName, 0666); err != nil {
		fmt.Println("Make named pipe file error:", err)
	}
}

// esegue il cleanup dell'ipc
func (comm *Communication) CleanupCommunication() {
	os.Remove(comm.pipe_name)
	comm.pipe.Close()
}

// legge dalla named pipe
func (comm *Communication) ReadFromPipe() (string, error) {
	if comm.scanner.Scan() {
		message := comm.scanner.Text()
		return message, nil
	} else {
		return "", comm.scanner.Err()
	}
}
