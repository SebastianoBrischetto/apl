package bot_communication

import (
	"bufio"
	"fmt"
	"os"
	"os/exec"
	"sync"
)

// createBot initializes the communication and starts the bot process.
func PlayAgainstBot(wg *sync.WaitGroup, pipeName string) {
	defer wg.Done()

	// Establish the connection
	comm, err := EstablishCommunication(pipeName)
	if err != nil {
		fmt.Println("Error establishing communication")
		return
	}
	defer comm.CleanupCommunication()

	// Start the bot process
	cmd := exec.Command("./cpp/build/ShipBattleBot", comm.go_cpp_pipe_name, comm.cpp_go_pipe_name)
	cmd.Stdout, cmd.Stderr = os.Stdout, os.Stderr
	if err := cmd.Start(); err != nil {
		fmt.Printf("Error starting C++: %v\n", err)
		return
	}
	defer CleanupBot(cmd)

	writer_scanner := bufio.NewScanner(os.Stdin)
	for {
		// Writing phase to the pipe
		fmt.Print("Enter text to send to C++ (exit to stop the execution): ")
		writer_scanner.Scan()
		inputText := writer_scanner.Text()
		if inputText == "exit" {
			break
		}

		comm.WriteToPipe(inputText)

		comm.ReadFromPipe()
	}
}

func CleanupBot(cmd *exec.Cmd) {
	if err := cmd.Process.Signal(os.Interrupt); err != nil {
		fmt.Printf("Error stopping C++ reader: %v\n", err)
		return
	}
	if err := cmd.Wait(); err != nil {
		fmt.Printf("Error waiting for C++ reader to exit: %v\n", err)
	}
}
