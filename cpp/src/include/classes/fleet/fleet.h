#ifndef FLEET_H_
#define FLEET_H_
#include "../include_ships.h"

enum ShipType{
    DESTROYER,
    SUBMARINE
};

class Fleet{
    public:
        Fleet(Ship& ship);
        Fleet(ShipType ship_type, int number_of_ships, Ocean& ocean);
        void addToFleet(Ship& ship);
        void addToFleet(ShipType ship_type, int number_of_ships, Ocean& ocean);

        bool getIsFleetDestroyed();
        Ship& getShip(int index);
        
    private:
        bool is_fleet_destroyed_;
        std::vector<Ship> fleet_;

        Ship createTypeOfShip(ShipType type, Ocean& ocean);
};

#endif