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

json getMoves(BotType opponent_id, Ocean& ocean, Fleet& fleet){
    BotAlgorithm* bot = nullptr;  
    switch(opponent_id){
        case RANDOM:
            bot = new Random(ocean, fleet);
            break;
        case HUNT_AND_TARGET:
            bot = new HuntAndTarget(ocean, fleet);
            break;
        case PARITY:
            bot = new Parity(ocean, fleet);
            break;
        case PROBABILITY:
            bot = new Probability(ocean, fleet);
            break;
    }
    json moves;
    while(!fleet.getIsFleetDestroyed()){
        json move;
        bot->doMove();
        move["x"] = bot->getLastHitX();
        move["y"] = bot->getLastHitY();
        moves["moves"].push_back(move);
    };
    delete bot;
    return moves;
}