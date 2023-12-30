#ifndef SUBMARINE_H_
#define SUBMARINE_H_
#include "../ship/ship.h"

class Submarine : public Ship {
    public:
        //Costruttore sottomarino eredita da ship
        Submarine(int init_x_cord, int init_y_cord, Direction direction, Ocean& ocean);
};

#endif