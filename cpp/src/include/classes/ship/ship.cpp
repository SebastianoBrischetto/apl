#include "ship.h"

Ship::Ship(int init_x_cord, int init_y_cord, Direction direction, int length, Ocean& ocean) : 
    length_(length),
    ocean_(ocean)
{
    if(ocean_.isSpaceOccupied(init_x_cord, init_y_cord, direction, length)){
        throw std::runtime_error("Space already occupied");
    }

    // Riserva lo spazio necessario in modo da evitare l'overhead dovuto allo shift durante l'inserimento
    ship_.reserve(length_);

    int x = init_x_cord;
    int y = init_y_cord;

    for(int i = 0; i < length; i++){
        ship_.emplace_back(ocean.getCell(x, y));
        getShipPiece(i).setIsOccupied();
        Ocean::updateCoordinates(x, y, x, y, 1, direction);
    }
}

Ship::Ship(Ocean& ocean) : ocean_(ocean) {}

int Ship::getLength() const { return length_; }

Ocean& Ship::getOcean() const { return ocean_; }

Cell& Ship::getShipPiece(int index) const {
    if(index >= getLength()){
        throw std::runtime_error("Out of bounds");
    }
    return ship_[index].get();
}

bool Ship::isShipSunk() {
    for(int i = 0; i < length_; i++){
        // Almeno 1 pezzo non affondato => nave non affondata
        if(!getShipPiece(i).getIsHit()){ 
            return false;
        }
    }
    return true;
}

Ship& Ship::operator=(const Ship& original) {
    if (this != &original) {
        length_ = original.getLength();
        ocean_ = original.getOcean();
        ship_.clear();

        for (int i = 0; i < length_; ++i) {
            ship_.emplace_back(original.getShipPiece(i));
        }
    }
    return *this;
}