#include "ship.h"

Ship::Ship(int init_x_cord, int init_y_cord, Direction direction, int length, Ocean& ocean) : 
    length_(length),
    ocean_(ocean)
{
    if(ocean_.isSpaceOccupied(init_x_cord, init_y_cord, direction, length)){
        throw std::runtime_error("Space already occupied");
    }
    //riserva direttamente tutto lo spazio necessario in memoria in modo da evitare l'overhead dovuto all'inserimento di elementi 
    //(vector salva gli elementi in memoria contigua, quindi l'inserimento di nuovi elementi richiede di shiftare i bit)
    ship_.reserve(length_);
    int x = init_x_cord;
    int y = init_y_cord;
    for(int i = 0; i < length; i++){
        //emplace_back inizializza e carica dentro il vettore l'oggetto (non viene creato un oggetto temporaneo)
        ship_.emplace_back(ocean.getCell(x, y));
        getPiece(i).setIsOccupied();
        Ocean::updateCoordinates(x, y, x, y, 1, direction);
    }
}

Ship::Ship(Ocean& ocean) : ocean_(ocean) {}

int Ship::getLength() const { return length_; }

Ocean& Ship::getOcean() const { return ocean_; }

Cell& Ship::getPiece(int index) const{
    if(index >= getLength()){
        throw std::runtime_error("Out of bounds");
    }
    return ship_[index].get();
}

bool Ship::isShipSunk() {
    for(int i = 0; i < length_; i++){
        // almeno 1 pezzo a galla => nave viva
        if(!getPiece(i).getIsHit()){ 
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
            ship_.emplace_back(original.getPiece(i));
        }
    }
    return *this; // Return a reference to the modified object
}