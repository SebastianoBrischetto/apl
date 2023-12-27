#include <iostream>
#include "include/classes/include_all.h"

enum direction{
    HORIZONTAL,  //0
    VERTICAL    //1
};

int main() {

    /*
    Submarine ship = Submarine(1,2, HORIZONTAL);
    int ship_length = ship.getDimension();
    for(int i = 0; i<ship_length; i++){
        std::cout << "Pezzo " << i << " della nave nella posizione: {" << ship.getXCord(i) << "," << ship.getYCord(i) << "}" << std::endl;
    }
    */

    Ocean ocean = Ocean(10,10);
    std::cout << "cell {1,2} has been hit? " << ocean.getCell(1,2).getIsHit() << std::endl;
    ocean.getCell(1,2).setIsHit();
    std::cout << "cell {1,2} has been hit? " << ocean.getCell(1,2).getIsHit() << std::endl;

    Submarine submarine = Submarine(1, 1, HORIZONTAL, ocean);
    for(int i = 0; i<submarine.getDimension(); i++){
        std::cout << "Piece " << i << " is hit? " << submarine.getPiece(i).getIsHit() << std::endl;
    }

    return 0;
}
