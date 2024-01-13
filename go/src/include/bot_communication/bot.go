package bot_communication

import (
	"encoding/json"
	"fmt"
	"golang/include/game_elements"
	"os"
	"os/exec"
	"time"
)

// Avvia il programma c++ per recuperare le mosse del bot
func PlayAgainstBot(pipeName string, gameData game_elements.GameData) (BotMoves, error) {
	// dati di inizializzazione
	jsonData, err := json.Marshal(gameData)
	if err != nil {
		return BotMoves{}, err
	}

	// stabilisce l'ipc
	comm, err := EstablishCommunication(pipeName)
	if err != nil {
		return BotMoves{}, err
	}
	defer comm.CleanupCommunication()

	// avvia il programma c++
	cmd := exec.Command("./include/ShipBattleBot", comm.pipe_name, string(jsonData))
	cmd.Stdout, cmd.Stderr = os.Stdout, os.Stderr
	if err := cmd.Start(); err != nil {
		return BotMoves{}, err
	}
	defer CleanupBot(cmd)

	// aspetta .5s per il programma c++ di finire
	time.Sleep(500 * time.Millisecond)

	// legge dal canale ipc (named pipe)
	botMovesString, err := comm.ReadFromPipe()
	if err != nil {
		return BotMoves{}, err
	}

	// converte la stringa letta in una struct
	var botMoves BotMoves
	if err := json.Unmarshal([]byte(botMovesString), &botMoves); err != nil {
		return BotMoves{}, err
	}

	// ritorna le mosse del bot
	return botMoves, nil
}

// Chiude l'ipc e aspetta che il bot venga chiuso
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
