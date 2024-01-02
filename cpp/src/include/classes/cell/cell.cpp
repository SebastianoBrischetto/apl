#include "cell.h"

Cell::Cell(int init_x_cord, int init_y_cord) :
    x_cord_(init_x_cord), 
    y_cord_(init_y_cord), 
    is_hit_(false), 
    is_occupied_(false), 
    occupied_probability_(0)
    {
}

int Cell::getXCord() const { return x_cord_; }

int Cell::getYCord() const { return y_cord_; }

bool Cell::getIsHit() const { return is_hit_; }

bool Cell::getIsOccupied() const { return is_occupied_; }

int Cell::getOccupiedProbability() const { return occupied_probability_; }

void Cell::setIsHit() {
    if(is_hit_){
        throw std::runtime_error("Space already hit");
    }
    is_hit_ = true;
}

void Cell::setIsOccupied() {
    if(is_occupied_){
        throw std::runtime_error("Space already occupied");
    }
    is_occupied_ = true;
}

void Cell::incraseOccupiedProbability(int n){ occupied_probability_ += n; }

void Cell::resetOccupiedProbability(){ occupied_probability_ = 0; }