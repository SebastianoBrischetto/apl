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
    Ocean player_ocean(gameData["columns"], gameData["rows"]);
    Fleet player_fleet(player_ocean);
    Ocean bot_ocean(gameData["columns"], gameData["rows"]);
    Fleet bot_fleet(bot_ocean);
    for(int i = 0; i < gameData["ships"].size(); i++){
        Ship ship = createShipFromJson(gameData["ships"][i], player_ocean);
        player_fleet.addToFleet(ship);
        bot_fleet.addToFleet(gameData["ships"][i]["ship_type"], 1, bot_ocean);
    }

    // Recupera i dati del bot e li scrive sulla named pipe
    json botData = getBotData(static_cast<BotType>(gameData["opponent_id"]), player_ocean, player_fleet, bot_fleet);
    pipeWriter << botData << std::endl;
    pipeWriter.close();
    return 0;
}

/*
#include "include/classes/utils/playgame.cpp"
int main(){
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    tryGame(10,10, 1, 1, 1, 1, 1, PROBABILITY);
}
*/
