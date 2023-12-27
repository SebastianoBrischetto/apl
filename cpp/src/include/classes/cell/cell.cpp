#include "cell.h"

Cell::Cell(int init_x_cord, int init_y_cord) {
    x_cord_ = init_x_cord;
    y_cord_ = init_y_cord;
    is_hit_ = false;
}
int Cell::getXCord() {
    return x_cord_;
}

int Cell::getYCord() {
    return y_cord_;
}

void Cell::setIsHit() {
    is_hit_ = true;
}

bool Cell::getIsHit() {
    return is_hit_;
}