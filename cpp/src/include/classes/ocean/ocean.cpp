#include "ocean.h"

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

Cell& Ocean::getCell(int x, int y){
    return ocean_[x + y * columns_];
}