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
    try {
        Cell& cell = ocean_.getCell(x, y);
        cell.setIsHit();
        if (cell.getIsOccupied()) {
            fleet_.updateFleetNumbersOnHit();
        }
    } catch (const std::exception&) {
        return false;
    }
    return true;
}