#ifndef BATTLESHIP_H_
#define BATTLESHIP_H_
#include "../ship/ship.h"

class Battleship : public Ship {
    public:
        //Costruttore battleship eredita da ship
        Battleship(int init_x_cord, int init_y_cord, Direction direction, Ocean& ocean);
};

#endif