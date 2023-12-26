#include <iostream>
#include <vector>
#include "include/ships/ship_block.h"

enum direction{
    HORIZONTAL,  //0
    VERTICAL    //1
};


class Ship{
public:
    virtual int dimension() = 0;

    virtual int getXCord(int piece) = 0;

    virtual int getYCord(int piece) = 0;

    void buildShip(int init_x_cord, int init_y_cord, int direction, int dimension, std::vector<ShipBlock>& ship){
        //riserva solo lo spazio necessario in modo da evitare l'overhead dovuto all'inserimento di elementi oltre la dimensione attuale
        ship.clear();
        ship.reserve(dimension);
        for(int i = 0; i < dimension; i++){
            if(direction == HORIZONTAL){
                ship.push_back(ShipBlock(init_x_cord+i, init_y_cord));
            }
            else{
                ship.push_back(ShipBlock(init_x_cord, init_y_cord+i));
            }
        }
    }

    virtual ~Ship() {}
};

class Destroyer : public Ship {
public:
    Destroyer(int init_x_cord, int init_y_cord, int direction){
        buildShip(init_x_cord, init_y_cord, direction, dimension_, ship_);
    }

    int dimension() override{
        return dimension_;
    }

    int getXCord(int piece) override{
        return ship_.at(piece).getXCord();
    }

    int getYCord(int piece) override{
        return ship_[piece].getYCord();
    }

private:
    const int dimension_ = 2;
    std::vector<ShipBlock> ship_;
};


int main() {
    Destroyer distruttore = Destroyer(0,0, HORIZONTAL);
    std::cout << "Primo pezzo del distruttore: {" << distruttore.getXCord(0) << "," << distruttore.getYCord(0) << "}" << std::endl;
    std::cout << "Secondo pezzo del distruttore: {" << distruttore.getXCord(1) << "," << distruttore.getYCord(1) << "}" << std::endl;

    return 0;
}
