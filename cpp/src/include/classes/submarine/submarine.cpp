#include "submarine.h"

Submarine::Submarine(int init_x_cord, int init_y_cord, int direction, Ocean ocean){
    dimension_ = 3;
    buildShip(init_x_cord, init_y_cord, direction, ocean);
}