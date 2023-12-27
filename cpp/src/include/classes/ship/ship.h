#ifndef SHIP_H_
#define SHIP_H_
#include "../ocean/ocean.h"
#include <functional>

class Ship{
    public:

        virtual ~Ship();

        int getDimension();

        Cell& getPiece(int piece);

    protected:
        int dimension_;
        std::vector<std::reference_wrapper<Cell>> ship_;

        void buildShip(int init_x_cord, int init_y_cord, int direction, Ocean& ocean);
};

#endif