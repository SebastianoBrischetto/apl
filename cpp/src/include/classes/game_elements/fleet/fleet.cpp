#include "fleet.h"

Fleet::Fleet(Ocean& ocean) :
    destroyers_(0),
    submarines_and_cruisers_(0),
    battleships_(0),
    carriers_(0),
    ocean_(ocean),
    last_sunk_ship_(ocean)
{
}

void Fleet::addToFleet(Ship& ship) {
    if(&getFleetOcean() != &ship.getOcean()){
        throw std::runtime_error("Non e possibile aggiungere navi appartenenti ad un oceano diverso");
    }
    fleet_.push_back(ship);
    updateFleetNumbers(ship, 1);
}

void Fleet::addToFleet(ShipType ship_type, int number_of_ships, Ocean& ocean) {
    if(&getFleetOcean() != &ocean){
        throw std::runtime_error("Non e possibile aggiungere navi appartenenti ad un oceano diverso");
    }
    for (int i = 0; i < number_of_ships; ++i) {
        while (true) {
            try {
                int x = rand() % ocean.getNumberOfColumns();
                int y = rand() % ocean.getNumberOfRows();
                Direction direction = static_cast<Direction>(std::rand() % 4);
                fleet_.emplace_back(Fleet::createTypeOfShip(ship_type, x, y, direction, ocean));
                break;
            } catch (const std::exception&) {
            }
        }
        updateFleetNumbers(fleet_.back(), 1);
    }
}

int Fleet::getNumberOfShips() { 
    return fleet_.size(); 
}

int Fleet::getNumberOfDestroyers() { 
    return destroyers_; 
}

int Fleet::getNumberOfSubmarinesAndCruisers() { 
    return submarines_and_cruisers_; 
}

int Fleet::getNumberOfBattleships() { 
    return battleships_; 
}

int Fleet::getNumberOfCarriers() { 
    return carriers_; 
}

Ship& Fleet::getShip(int i) {
    if(i >= getNumberOfShips()){
        throw std::runtime_error("Non e possibile recuperare la nave - out of bounds");
    }
    auto it = std::next(fleet_.begin(), i);
    return *it;
}

Ship& Fleet::getLastSunkShip() { 
    return last_sunk_ship_; 
}

Ocean& Fleet::getFleetOcean() {
    return ocean_;
}

bool Fleet::getIsFleetDestroyed() { 
    return fleet_.empty(); 
}

void Fleet::updateFleetNumbers(Ship& ship, int value) {
    switch (ship.getLength()) {
        case DESTROYER:
            destroyers_ += value;
            break;
        case SUBMARINE:
            submarines_and_cruisers_ += value;
            break;
        case BATTLESHIP:
            battleships_ += value;
            break;
        case CARRIER:
            carriers_ += value;
            break;
    }
}

void Fleet::updateFleetNumbersOnHit() {
    for (auto it = fleet_.begin(); it != fleet_.end();) {
        if (it->isShipSunk()) {
            updateFleetNumbers(*it, -1);
            last_sunk_ship_ = *it;
            it = fleet_.erase(it);
        } else {
            ++it;
        }
    }
}

Ship Fleet::createTypeOfShip(ShipType ship_type, int x, int y, Direction direction ,Ocean& ocean) {
    switch (ship_type) {
        case DESTROYER:
            return Destroyer(x, y, direction, ocean);
        case SUBMARINE:
            return Submarine(x, y, direction, ocean);
        case CRUISER:
            return Cruiser(x, y, direction, ocean);
        case BATTLESHIP:
            return Battleship(x, y, direction, ocean);
        case CARRIER:
            return Carrier(x, y, direction, ocean);
        default:
            throw std::runtime_error("Type of ship not supported");
    }
}
