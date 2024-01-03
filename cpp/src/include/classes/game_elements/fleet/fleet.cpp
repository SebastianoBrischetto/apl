#include "fleet.h"

Fleet::Fleet(Ship& ship) :
    destroyers_(0),
    submarines_and_cruisers_(0),
    battleships_(0),
    carriers_(0),
    last_sunk_ship_(ship.getOcean())
{
    addToFleet(ship);
}

Fleet::Fleet(ShipType ship_type, int number_of_ships, Ocean& ocean) :
    destroyers_(0),
    submarines_and_cruisers_(0),
    battleships_(0),
    carriers_(0),
    last_sunk_ship_(ocean)
{
    addToFleet(ship_type, number_of_ships, ocean);
}

void Fleet::addToFleet(Ship& ship) {
    fleet_.push_back(ship);
    updateFleetNumbers(ship, 1);
}

void Fleet::addToFleet(ShipType ship_type, int number_of_ships, Ocean& ocean) {
    for (int i = 0; i < number_of_ships; ++i) {
        while (true) {
            try {
                fleet_.emplace_back(createTypeOfShip(ship_type, ocean));
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

Ship& Fleet::getLastSunkShip() { 
    return last_sunk_ship_; 
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

Ship Fleet::createTypeOfShip(ShipType ship_type, Ocean& ocean) {
    int x = rand() % ocean.getNumberOfColumns();
    int y = rand() % ocean.getNumberOfRows();
    Direction direction = static_cast<Direction>(std::rand() % 4);
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
