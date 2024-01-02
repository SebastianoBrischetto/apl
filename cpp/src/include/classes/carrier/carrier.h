#ifndef CARRIER_H_
#define CARRIER_H_

#include "../ship/ship.h"

class Carrier : public Ship {

public:
    Carrier(int init_x_cord, int init_y_cord, Direction direction, Ocean& ocean);
};

#endif