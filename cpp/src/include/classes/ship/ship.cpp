#include "ship.h"

enum direction{
    HORIZONTAL,  //0
    VERTICAL    //1
};

Ship::~Ship(){}

int Ship::getDimension(){
    return dimension_;
}

Cell& Ship::getPiece(int piece){
    return ship_[piece].get();
}

void Ship::buildShip(int init_x_cord, int init_y_cord, int direction, Ocean& ocean){
    ship_.clear();
    ship_.reserve(dimension_);
    for(int i = 0; i < dimension_; i++){
        if(direction == HORIZONTAL){
            ship_.push_back(ocean.getCell(init_x_cord + i, init_y_cord));
        }
        else{
            ship_.push_back(ocean.getCell(init_x_cord, init_y_cord + i));
        }
    }
}
