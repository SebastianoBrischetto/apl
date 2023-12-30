#ifndef CRUISER_H_
#define CRUISER_H_
#include "../ship/ship.h"

class Cruiser : public Ship {
    public:
        //Costruttore cruiser eredita da ship
        Cruiser(int init_x_cord, int init_y_cord, Direction direction, Ocean& ocean);
};

#endif