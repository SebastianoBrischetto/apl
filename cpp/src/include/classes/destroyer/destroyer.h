#ifndef DESTROYER_H_
#define DESTROYER_H_
#include "../ship/ship.h"

class Destroyer : public Ship {
    public:
        Destroyer(int init_x_cord, int init_y_cord, int direction, Ocean ocean);
};

#endif