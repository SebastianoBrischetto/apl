#include "ocean.h"

enum direction{
    HORIZONTAL,  //0
    VERTICAL    //1
};

Ocean::Ocean(int columns, int rows){
    columns_ = columns;
    rows_ = rows;
    dimension_ = columns_* rows_;
    //riserva solo lo spazio necessario in modo da evitare l'overhead dovuto all'inserimento di elementi oltre la dimensione attuale
    ocean_.clear();
    ocean_.reserve(dimension_);
    for(int i = 0; i < dimension_; i++){
        ocean_.push_back(Cell(i%columns_,i/columns_));
    }
}

bool Ocean::isSpaceOccupied(int init_x_cord, int init_y_cord, int direction, int length){
    for(int i = 0; i < length; i++){
        if(direction == HORIZONTAL && getCell(init_x_cord + i, init_y_cord).getIsOccupied()){
            return true;
        }
        else if(direction == VERTICAL && getCell(init_x_cord, init_y_cord + i).getIsOccupied()){
            return true;
        }
    }
    return false;
}

int Ocean::getNumberOfRows(){
    return rows_;
}
int Ocean::getNumberOfColumns(){
    return columns_;
}

Cell& Ocean::getCell(int x, int y){
    if(x >= columns_ || y >= rows_){
        throw std::runtime_error("Out of bounds");
    }
    return ocean_[x + y * columns_];
}