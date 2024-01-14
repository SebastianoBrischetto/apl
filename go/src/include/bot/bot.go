// Pacchetto bot gestisce la comunicazione con il programma bot.
package bot

import (
	"encoding/json"
	"fmt"
	"golang/include/game_elements"
	"os"
	"os/exec"
	"time"
)

// PlayAgainstBot avvia il programma C++ per ottenere le mosse del bot.
// Restituisce le mosse del bot o un eventuale errore.
func PlayAgainstBot(pipe_name string, game_data game_elements.GameData) (BotMoves, error) {
	// Serializza i dati di gioco in formato JSON
	json_data, err := json.Marshal(game_data)
	if err != nil {
		return BotMoves{}, err
	}

	// Stabilisce la IPC
	ipc, err := EstablishCommunication(pipe_name)
	if err != nil {
		return BotMoves{}, err
	}
	defer ipc.CleanupCommunication()

	// Avvia il programma C++
	bot := exec.Command("./include/ShipBattleBot", ipc.pipe_name, string(json_data))
	bot.Stdout, bot.Stderr = os.Stdout, os.Stderr
	if err := bot.Start(); err != nil {
		return BotMoves{}, err
	}
	defer CleanupBot(bot)

	// Attende 0.5 secondi affinché il programma C++ finisca
	time.Sleep(500 * time.Millisecond)

	// Legge il risultato del programma
	results, err := ipc.ReadFromPipe()
	if err != nil {
		return BotMoves{}, err
	}

	// Converte il risultato in una struttura BotMoves
	var bot_moves BotMoves
	if err := json.Unmarshal([]byte(results), &bot_moves); err != nil {
		return BotMoves{}, err
	}

	// Restituisce le mosse del bot
	return bot_moves, nil
}

// CleanupBot chiude la comunicazione IPC e attende la chiusura del bot.
func CleanupBot(bot *exec.Cmd) {
	if err := bot.Process.Signal(os.Interrupt); err != nil {
		fmt.Printf("Errore durante l'arresto del lettore C++: %v\n", err)
		return
	}
	if err := bot.Wait(); err != nil {
		fmt.Printf("Errore durante l'attesa della chiusura del lettore C++: %v\n", err)
	}
	fmt.Printf("Programma C++ chiuso\n")
}
