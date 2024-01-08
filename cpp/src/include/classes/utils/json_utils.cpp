#include "json.hpp"
#include "../game_elements/include_game_elements.h"
#include "../bot/include_bots.h"

using json = nlohmann::json;

Ship createShipFromJson(json ship, Ocean& ocean){
    ShipType ship_type = ship["ship_type"];
    int init_x = ship["init_x"];
    int init_y = ship["init_y"];
    Direction direction = ship["direction"];
    return Fleet::createTypeOfShip(ship_type, init_x, init_y, direction, ocean);
}

json getBotData(BotType opponent_id, Ocean& player_ocean, Fleet& player_fleet, Fleet& bot_fleet){
    json botData;
    for(int i = 0; i < bot_fleet.getNumberOfShips(); i++){
        Ship& current_ship = bot_fleet.getShip(i);
        for(int j = 0; j < current_ship.getLength(); j++){
            json coords;
            coords["x"] = current_ship.getShipPiece(j).getXCoord();
            coords["y"] = current_ship.getShipPiece(j).getYCoord();
            botData["occupied_coords"].push_back(coords);
        }
    }
    BotAlgorithm* bot = nullptr;  
    switch(opponent_id){
        case RANDOM:
            bot = new Random(player_ocean, player_fleet);
            break;
        case HUNT_AND_TARGET:
            bot = new HuntAndTarget(player_ocean, player_fleet);
            break;
        case PARITY:
            bot = new Parity(player_ocean, player_fleet);
            break;
        case PROBABILITY:
            bot = new Probability(player_ocean, player_fleet);
            break;
    }
    while(!player_fleet.getIsFleetDestroyed()){
        json coords;
        bot->doMove();
        coords["x"] = bot->getLastHitX();
        coords["y"] = bot->getLastHitY();
        botData["moves"].push_back(coords);
    };
    delete bot;
    return botData;
}