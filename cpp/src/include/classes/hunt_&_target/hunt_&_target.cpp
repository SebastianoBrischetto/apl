#include "hunt_&_target.h"

HuntAndTarget::HuntAndTarget(Ocean& ocean, Fleet& fleet) : 
    BotAlgorithm(ocean, fleet)
{}

void HuntAndTarget::doMove() {
    if (counter_ >= columns_ * rows_) {
        return;
    }
    if (target_list_.empty()) {
        hunt();
    } else {
        target();
    }
    counter_++;
}

void HuntAndTarget::hunt() {
    while (true) {
        int x = rand() % columns_;
        int y = rand() % rows_;
        if (hitAndNotify(x, y)) {
            addCloseCells(x, y);
            break;
        }
    }
}

void HuntAndTarget::addCloseCells(int x, int y) {
    if (ocean_.getCell(x, y).getIsOccupied()) {
        for(Direction dir : {UP, RIGHT, DOWN, LEFT}){
            int new_target_x;
            int new_target_y;
            Ocean::updateCoordinates(x, y, new_target_x, new_target_y, 1, dir);
            addToTargets(new_target_x, new_target_y);
        }
    }
}

void HuntAndTarget::addToTargets(int x, int y) {
    if (ocean_.areCoordinatesValid(x, y) && !ocean_.getCell(x, y).getIsHit()) {
        target_list_.emplace_back(ocean_.getCell(x, y));
    }
}

void HuntAndTarget::target() {
    while(true){
        Cell& last_target = target_list_.front().get();
        target_list_.pop_front();
        if (!last_target.getIsHit()) {
            int x = last_target.getXCoord();
            int y = last_target.getYCoord();
            if (hitAndNotify(x, y)) {
                addCloseCells(x, y);
            }
            break;
        }
    }
}