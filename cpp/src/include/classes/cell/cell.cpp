#include "cell.h"

Cell::Cell(int init_x_cord, int init_y_cord) {
    x_cord_ = init_x_cord;
    y_cord_ = init_y_cord;
    is_hit_ = false;
    is_occupied_ = false;
}
int Cell::getXCord() {
    return x_cord_;
}

int Cell::getYCord() {
    return y_cord_;
}

bool Cell::getIsHit() {
    return is_hit_;
}

bool Cell::getIsOccupied() {
    return is_occupied_;
}

void Cell::setIsHit() {
    if(is_hit_){
        throw std::runtime_error("Space already hit");
    }
    is_hit_ = true;
}

void Cell::setIsOccupied() {
    is_occupied_ = true;
}