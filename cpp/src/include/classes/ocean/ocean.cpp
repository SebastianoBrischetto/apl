#include "ocean.h"

Ocean::Ocean(int columns, int rows) : columns_(columns), rows_(rows){
    int dimension = columns_* rows_;
    //riserva direttamente tutto lo spazio necessario in memoria in modo da evitare l'overhead dovuto all'inserimento di elementi 
    //(vector salva gli elementi in memoria contigua, quindi l'inserimento di nuovi elementi richiede di shiftare i bit)
    ocean_.clear();
    ocean_.reserve(dimension);
    for(int i = 0; i < dimension; i++){
        ocean_.push_back(Cell(i%columns_, i/columns_));
    }
}

bool Ocean::isSpaceOccupied(int init_x_cord, int init_y_cord, Direction direction, int length){
    int x = init_x_cord;
    int y = init_y_cord;
    for(int i = 0; i < length; i++){
        if(getCell(x, y).getIsOccupied()){
            return true;
        }
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
    return false;
}

int Ocean::getNumberOfRows(){
    return rows_;
}
int Ocean::getNumberOfColumns(){
    return columns_;
}

Cell& Ocean::getCell(int x, int y){
    if((x < 0 || x >= columns_) || (y < 0 || y >= rows_)){
        throw std::runtime_error("Out of bounds");
    }
    return ocean_[x + y * columns_];
}