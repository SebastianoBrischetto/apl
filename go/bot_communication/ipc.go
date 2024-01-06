package bot_communication

import (
	"bufio"
	"fmt"
	"os"
	"syscall"
)

// Communication struct represents the communication channels.
type Communication struct {
	go_cpp_pipe_name string
	cpp_go_pipe_name string
	writer_pipe      *os.File
	reader_pipe      *os.File
	reader_scanner   *bufio.Scanner
}

// establishCommunication creates and opens the named pipes for communication.
func EstablishCommunication(pipeName string) (*Communication, error) {
	goCppPipe := pipeName + "_go"
	cppGoPipe := pipeName + "_cpp"

	// Create the named pipes
	CreateNamedPipe(goCppPipe)
	CreateNamedPipe(cppGoPipe)

	// Open the writing pipe
	writer, err := os.OpenFile(goCppPipe, os.O_RDWR|os.O_APPEND, os.ModeNamedPipe)
	if err != nil {
		return nil, fmt.Errorf("error opening file: %v", err)
	}

	// Open the reading pipe
	reader, err := os.OpenFile(cppGoPipe, os.O_RDWR, os.ModeNamedPipe)
	if err != nil {
		return nil, fmt.Errorf("error opening file for reading: %v", err)
	}

	reader_scanner := bufio.NewScanner(reader)

	return &Communication{
			go_cpp_pipe_name: goCppPipe, cpp_go_pipe_name: cppGoPipe,
			writer_pipe: writer, reader_pipe: reader,
			reader_scanner: reader_scanner},
		nil
}

// createNamedPipe creates a named pipe.
func CreateNamedPipe(pipeName string) {
	os.Remove(pipeName)
	if err := syscall.Mkfifo(pipeName, 0666); err != nil {
		fmt.Println("Make named pipe file error:", err)
	}
}

func (comm *Communication) CleanupCommunication() {
	os.Remove(comm.go_cpp_pipe_name)
	os.Remove(comm.cpp_go_pipe_name)
	comm.writer_pipe.Close()
	comm.reader_pipe.Close()
}

func (comm *Communication) WriteToPipe(text string) error {
	if _, err := comm.writer_pipe.WriteString(text + "\n"); err != nil {
		fmt.Println("Error writing to named pipe:", err)
		return err
	}
	return nil
}

func (comm *Communication) ReadFromPipe() (string, error) {
	if comm.reader_scanner.Scan() {
		message := comm.reader_scanner.Text()
		fmt.Println("\033[34m Go - Message from C++ : \033[0m", message)
		return message, nil
	} else {
		err := comm.reader_scanner.Err()
		fmt.Println("Error reading from named pipe:", err)
		return "", err
	}
}
