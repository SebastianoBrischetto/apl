package bot_communication

import (
	"encoding/json"
	"fmt"
	"golang/go/src/include/game_elements"
	"os"
	"os/exec"
	"time"
)

func PlayAgainstBot(pipeName string, gameData game_elements.GameData) (game_elements.BotMoves, error) {
	jsonData, err := json.Marshal(gameData)
	if err != nil {
		return game_elements.BotMoves{}, err
	}

	// Crea l'ipc
	comm, err := EstablishCommunication(pipeName)
	if err != nil {
		return game_elements.BotMoves{}, err
	}
	defer comm.CleanupCommunication()

	// Inizia il processo bot
	cmd := exec.Command("./cpp/build/ShipBattleBot", comm.pipe_name, string(jsonData))
	cmd.Stdout, cmd.Stderr = os.Stdout, os.Stderr
	if err := cmd.Start(); err != nil {
		return game_elements.BotMoves{}, err
	}
	defer CleanupBot(cmd)
	time.Sleep(500 * time.Millisecond)

	botMovesString, err := comm.ReadFromPipe()
	if err != nil {
		return game_elements.BotMoves{}, err
	}

	var botMoves game_elements.BotMoves
	if err := json.Unmarshal([]byte(botMovesString), &botMoves); err != nil {
		return game_elements.BotMoves{}, err
	}
	return botMoves, nil
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
