package bot_communication

import (
	"encoding/json"
	"fmt"
	"golang/go/src/include/game_elements"
	"os"
	"os/exec"
	"time"
)

func PlayAgainstBot(pipeName string, gameData game_elements.GameData) {
	jsonData, err := json.Marshal(gameData)
	if err != nil {
		fmt.Println("Error marshaling GameData to JSON:", err)
		return
	}

	// Crea l'ipc
	comm, err := EstablishCommunication(pipeName)
	if err != nil {
		fmt.Println("Error establishing communication")
		return
	}
	defer comm.CleanupCommunication()

	// Inizia il processo bot
	cmd := exec.Command("./cpp/build/ShipBattleBot", comm.pipe_name, string(jsonData))
	cmd.Stdout, cmd.Stderr = os.Stdout, os.Stderr
	if err := cmd.Start(); err != nil {
		fmt.Printf("Error starting C++: %v\n", err)
		return
	}
	defer CleanupBot(cmd)
	time.Sleep(500 * time.Millisecond)
	comm.ReadFromPipe()
}

func CleanupBot(cmd *exec.Cmd) {
	if err := cmd.Process.Signal(os.Interrupt); err != nil {
		fmt.Printf("Error stopping C++ reader: %v\n", err)
		return
	}
	if err := cmd.Wait(); err != nil {
		fmt.Printf("Error waiting for C++ reader to exit: %v\n", err)
	}
	fmt.Printf("C++ closed\n")
}
