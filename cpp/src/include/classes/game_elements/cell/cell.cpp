#include "cell.h"

Cell::Cell(int init_x_coord, int init_y_coord) :
    x_coord_(init_x_coord),
    y_coord_(init_y_coord),
    is_hit_(false),
    is_occupied_(false),
    occupied_probability_(0)
{
}

int Cell::getXCoord() const {
    return x_coord_;
}

int Cell::getYCoord() const {
    return y_coord_;
}

bool Cell::getIsHit() const {
    return is_hit_;
}

bool Cell::getIsOccupied() const {
    return is_occupied_;
}

int Cell::getOccupiedProbability() const {
    return occupied_probability_;
}

void Cell::setIsHit() {
    if (is_hit_) {
        throw std::runtime_error("Cella già colpita");
    }
    is_hit_ = true;
}

void Cell::setIsOccupied() {
    if (is_occupied_) {
        throw std::runtime_error("Cella già occupata");
    }
    is_occupied_ = true;
}

void Cell::increaseOccupiedProbability(int n) {
    occupied_probability_ += n;
}

void Cell::resetOccupiedProbability() {
    occupied_probability_ = 0;
}
