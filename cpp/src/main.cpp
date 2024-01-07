#include <iostream>
#include <fstream>
#include "include/classes/utils/json_utils.cpp"
#include "include/classes/game_elements/include_game_elements.h"
#include "include/classes/bot/include_bots.h"

int main(int argc, char *argv[]) {
    // Controllo che il programma sia stato avviato in modo corretto
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <named_pipe_file>" << std::endl;
        return 1;
    }

    // Apro la named pipe su cui verra scritto il risultato
    const std::string pipe = argv[1];
    std::fstream pipeWriter(pipe, std::ios::app);
    if (!pipeWriter.is_open()) {
        std::cerr << "Error opening named pipe for writing: " << pipe << std::endl;
        return 1;
    }

    // Effettuo il parse del json
    const std::string stringGameData = argv[2];
    json gameData;
    try{
        gameData = json::parse(stringGameData);
    } catch (const std::exception& e) {
        pipeWriter << "Error parsing JSON: " << e.what() << std::endl;
        pipeWriter.close();
        return 1;
    }
    
    // Inizializzo la game board
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    Ocean ocean(gameData["columns"], gameData["rows"]);
    Ship ship = createShipFromJson(gameData["ships"][0], ocean);
    Fleet fleet(ship);
    for(int i = 1; i < gameData["ships"].size(); i++){
        Ship ship = createShipFromJson(gameData["ships"][i], ocean);
        fleet.addToFleet(ship);
    }

    // Recupera le mosse del bot e le scrive sulla named pipe
    json moves = getMoves(static_cast<BotType>(gameData["opponent_id"]), ocean, fleet);
    pipeWriter << moves << std::endl;
    pipeWriter.close();
    return 0;
}

/*
#include "include/classes/utils/playgame.cpp"
int main(){
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    tryGame(10,10, 1, 1, 1, 1, 1, RANDOM);
}
*/