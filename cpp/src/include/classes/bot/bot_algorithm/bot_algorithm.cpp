#include "bot_algorithm.h"

BotAlgorithm::BotAlgorithm(Ocean& ocean, Fleet& fleet) : 
    ocean_(ocean), 
    fleet_(fleet),
    counter_(0),
    last_hit_x_(-1),
    last_hit_y_(-1)
{
    rows_ = ocean_.getNumberOfRows();
    columns_ = ocean_.getNumberOfColumns();
}

int BotAlgorithm::getCounter() {
    return counter_;
}

int BotAlgorithm::getLastHitX(){
    return last_hit_x_;
}

int BotAlgorithm::getLastHitY(){
    return last_hit_y_;
}

bool BotAlgorithm::hitAndNotify(int x, int y) {
    Cell& cell = ocean_.getCell(x, y);
    if(cell.getIsHit()){
        return false;
    }
    cell.setIsHit();
    last_hit_x_ = x;
    last_hit_y_ = y;
    if (cell.getIsOccupied()) {
        fleet_.updateFleetNumbersOnHit();
    }
    return true;
}