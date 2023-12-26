#include <iostream>
#include "ships/ship_block.h"

int main() {
    // Create an object of MyClass
    ShipBlock first_piece = ShipBlock(1,5);

    // Call a member function of the object
    std::cout << "First piece cords: {" << first_piece.getXCord() << "," << first_piece.getYCord() << "}" << std::endl;

    return 0;
}
