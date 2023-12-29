#include "ship.h"

enum direction{
    HORIZONTAL,  //0
    VERTICAL    //1
};

Ship::Ship(int init_x_cord, int init_y_cord, int direction, int length, Ocean& ocean){
    if(ocean.isSpaceOccupied(init_x_cord, init_y_cord, direction, length)){
        throw std::runtime_error("Space already occupied");
    }
    length_ = length;
    ship_.clear();
    ship_.reserve(length_);
    for(int i = 0; i < length_; i++){
        if(direction == HORIZONTAL){
            ship_.push_back(ocean.getCell(init_x_cord + i, init_y_cord));
            ocean.getCell(init_x_cord + i, init_y_cord).setIsOccupied();
        }
        else{
            ship_.push_back(ocean.getCell(init_x_cord, init_y_cord + i));
            ocean.getCell(init_x_cord, init_y_cord + i).setIsOccupied();
        }
    }
}

int Ship::getLength(){
    return length_;
}

Cell& Ship::getPiece(int piece){
    return ship_[piece].get();
}
