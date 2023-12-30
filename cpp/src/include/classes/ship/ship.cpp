#include "ship.h"

Ship::Ship(int init_x_cord, int init_y_cord, Direction direction, int length, Ocean& ocean) : length_(length), is_sunk_(false), ocean_(ocean){
    if(ocean_.isSpaceOccupied(init_x_cord, init_y_cord, direction, length)){
        throw std::runtime_error("Space already occupied");
    }
    //riserva direttamente tutto lo spazio necessario in memoria in modo da evitare l'overhead dovuto all'inserimento di elementi 
    //(vector salva gli elementi in memoria contigua, quindi l'inserimento di nuovi elementi richiede di shiftare i bit)
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
        // almeno 1 pezzo a galla => nave viva
        if(!getPiece(i).getIsHit()){ 
            is_sunk_ = false;
        }
    }
    return is_sunk_;
}

Cell& Ship::getPiece(int index){
    if(index >= getLength()){
        throw std::runtime_error("Out of bounds");
    }
    return ship_[index].get();
}
