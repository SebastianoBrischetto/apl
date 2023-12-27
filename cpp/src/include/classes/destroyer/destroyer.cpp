#include "destroyer.h"

Destroyer::Destroyer(int init_x_cord, int init_y_cord, int direction, Ocean ocean){
    dimension_ = 2;
    buildShip(init_x_cord, init_y_cord, direction, ocean);
}