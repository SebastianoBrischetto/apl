package bot_communication

import (
	"bufio"
	"fmt"
	"os"
	"syscall"
)

// Communication struct represents the communication channels.
type Communication struct {
	pipe_name string
	pipe      *os.File
	scanner   *bufio.Scanner
}

// establishCommunication creates and opens the named pipes for communication.
func EstablishCommunication(pipeName string) (*Communication, error) {
	// Create the named pipes
	CreateNamedPipe(pipeName)

	// Open the reading pipe
	pipe, err := os.OpenFile(pipeName, os.O_RDWR, os.ModeNamedPipe)
	if err != nil {
		return nil, fmt.Errorf("error opening file for reading: %v", err)
	}

	scanner := bufio.NewScanner(pipe)

	return &Communication{pipe_name: pipeName, pipe: pipe, scanner: scanner}, nil
}

// createNamedPipe creates a named pipe.
func CreateNamedPipe(pipeName string) {
	os.Remove(pipeName)
	if err := syscall.Mkfifo(pipeName, 0666); err != nil {
		fmt.Println("Make named pipe file error:", err)
	}
}

func (comm *Communication) CleanupCommunication() {
	os.Remove(comm.pipe_name)
	comm.pipe.Close()
}

func (comm *Communication) ReadFromPipe() (string, error) {
	if comm.scanner.Scan() {
		message := comm.scanner.Text()
		fmt.Println("\033[34m Go - Message from C++ : \033[0m", message)
		return message, nil
	} else {
		err := comm.scanner.Err()
		fmt.Println("Error reading from named pipe:", err)
		return "", err
	}
}
