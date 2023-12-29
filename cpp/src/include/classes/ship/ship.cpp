#include "ship.h"

Ship::Ship(int init_x_cord, int init_y_cord, Direction direction, int length, Ocean& ocean){
    if(ocean.isSpaceOccupied(init_x_cord, init_y_cord, direction, length)){
        throw std::runtime_error("Space already occupied");
    }
    length_ = length;
    is_sunk_ = false;
    ship_.clear();
    ship_.reserve(length_);
    int x = init_x_cord;
    int y = init_y_cord;
    for(int i = 0; i < length; i++){
        ship_.push_back(ocean.getCell(x, y));
        getPiece(i).setIsOccupied();
        switch(direction){
            case UP:
                y--;
                break;
            case RIGHT:
                x++;
                break;
            case DOWN:
                y++;
                break;
            case LEFT:
                x--;
                break;
        }
    }
}

int Ship::getLength(){
    return length_;
}

bool Ship::getIsSunk(){
    is_sunk_ = true;
    for(int i = 0; i < length_; i++){
        if(!getPiece(i).getIsHit()){  // almeno 1 pezzo a galla => nave viva
            is_sunk_ = false;
        }
    }
    return is_sunk_;
}

Cell& Ship::getPiece(int index){
    return ship_[index].get();
}
