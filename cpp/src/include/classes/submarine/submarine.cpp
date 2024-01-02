#include "submarine.h"

Submarine::Submarine(int init_x_cord, int init_y_cord, Direction direction, Ocean& ocean) : 
    Ship(init_x_cord, init_y_cord, direction, 3, ocean)
{}