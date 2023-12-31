#include "bot_algorithm.h"
BotAlgorithm::BotAlgorithm(Ocean& ocean, Fleet& fleet) : ocean_(ocean), fleet_(fleet){
    rows_ = ocean_.getNumberOfRows();
    columns_ = ocean_.getNumberOfColumns();
}

bool BotAlgorithm::hitAndNotify(int x, int y){
    try{
        ocean_.getCell(x, y).setIsHit();
    }catch(const std::exception& e){
        return false;
    };
    if(ocean_.getCell(x,y).getIsOccupied()){
        fleet_.updateFleetStatus();
    }
    return true;
}