#include "fleet.h"

Fleet::Fleet(Ship& ship){
    addToFleet(ship);
}

Fleet::Fleet(ShipType ship_type, int number_of_ships, Ocean& ocean){
    addToFleet(ship_type, number_of_ships, ocean);
}

void Fleet::addToFleet(Ship& ship){
    is_fleet_destroyed_ = false;
    fleet_.push_back(ship);
}

void Fleet::addToFleet(ShipType ship_type, int number_of_ships, Ocean& ocean){
    is_fleet_destroyed_ = false;
    for(int i=0; i<number_of_ships; i++){
        while(true){
            try{
                fleet_.push_back(createTypeOfShip(ship_type, ocean));
                break;
            }catch(const std::exception& e){}
        }
    }
}

bool Fleet::getIsFleetDestroyed(){
    is_fleet_destroyed_ = true;
    for(int i = 0; i < fleet_.size(); i++){
        if(!fleet_[i].getIsSunk()){  // se almeno 1 nave a galla => flotta viva
            is_fleet_destroyed_ = false;
        }
    }
    return is_fleet_destroyed_;
}

Ship& Fleet::getShip(int index){
    return fleet_[index];
}

Ship Fleet::createTypeOfShip(ShipType type, Ocean& ocean){
    switch(type){
        case DESTROYER:
            return Destroyer(rand()%ocean.getNumberOfColumns(), rand()%ocean.getNumberOfRows(), static_cast<Direction>(std::rand()%4), ocean);
            break;
        case SUBMARINE:
            return Submarine(rand()%ocean.getNumberOfColumns(), rand()%ocean.getNumberOfRows(), static_cast<Direction>(std::rand()%4), ocean);
            break;
        default: 
            throw std::runtime_error("Type of ship not supported");
    }   
}

