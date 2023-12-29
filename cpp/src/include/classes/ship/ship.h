#ifndef SHIP_H_
#define SHIP_H_
#include <functional>
#include "../ocean/ocean.h"

class Ship{
    public:
        Ship(int init_x_cord, int init_y_cord, Direction direction, int length, Ocean& ocean);

        int getLength();
        bool getIsSunk();
        Cell& getPiece(int index);

    private:
        int length_;
        bool is_sunk_;
        std::vector<std::reference_wrapper<Cell>> ship_;
};

#endif