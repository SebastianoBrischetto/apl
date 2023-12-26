#include "ship_block.h"

ShipBlock::ShipBlock(int init_x_cord, int init_y_cord) {
    x_cord_ = init_x_cord;
    y_cord_ = init_y_cord;
}
int ShipBlock::getXCord() {
    return x_cord_;
}

int ShipBlock::getYCord() {
    return y_cord_;
}