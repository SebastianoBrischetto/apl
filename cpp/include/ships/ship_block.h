#ifndef SHIP_BLOCK_H_
#define SHIP_BLOCK_H_

class ShipBlock {
public:
    ShipBlock(int init_x_cord, int init_y_cord);
    int getXCord();
    int getYCord();

private:
    int x_cord_;
    int y_cord_;
};

#endif