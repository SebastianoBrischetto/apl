#ifndef SHIP_H_
#define SHIP_H_
#include <functional>
#include "../ocean/ocean.h"

class Ship{
    public:
        Ship(int init_x_cord, int init_y_cord, int direction, int length, Ocean& ocean);

        int getLength();

        Cell& getPiece(int piece);

    private:
        int length_;
        std::vector<std::reference_wrapper<Cell>> ship_;
};

#endif