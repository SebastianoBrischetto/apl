#include "bot_algorithm.h"

BotAlgorithm::BotAlgorithm(Ocean& ocean, Fleet& fleet) : 
    ocean_(ocean), 
    fleet_(fleet),
    counter_(0)
{
    rows_ = ocean_.getNumberOfRows();
    columns_ = ocean_.getNumberOfColumns();
}

int BotAlgorithm::getCounter() {
    return counter_;
}

bool BotAlgorithm::hitAndNotify(int x, int y) {
    Cell& cell = ocean_.getCell(x, y);
    if(cell.getIsHit()){
        return false;
    }
    cell.setIsHit();
    if (cell.getIsOccupied()) {
        fleet_.updateFleetNumbersOnHit();
    }
    return true;
}