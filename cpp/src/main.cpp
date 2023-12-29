#include <iostream>
#include "include/classes/include_all.h"

enum direction{
    HORIZONTAL,  //0
    VERTICAL    //1
};

void showOccupiedCells(Ocean ocean);
void showHitCells(Ocean ocean);

int main() {
    Ocean ocean = Ocean(10,10);
    Submarine submarine1 = Submarine(7, 9, HORIZONTAL, ocean);
    Submarine submarine2 = Submarine(2, 0, VERTICAL, ocean);
    Submarine submarine3 = Submarine(1, 1, HORIZONTAL, ocean);
    showOccupiedCells(ocean);
    return 0;
}


void showOccupiedCells(Ocean ocean){
    for(int x = 0; x < ocean.getNumberOfColumns(); x++){
        std::cout << "  |  " << x;
    };
    std::cout << std::endl << "--------------------------------------------------------------" << std::endl;
    std::string symbol;
    for(int y = 0; y < ocean.getNumberOfRows(); y++){
        std:: cout << y << " | ";
        for(int x = 0; x < ocean.getNumberOfColumns(); x++){
            symbol = ((ocean.getCell(x,y).getIsOccupied())? "o" : " ");
            std::cout << " " << symbol << "  | ";
        }
        std::cout << std::endl << "--------------------------------------------------------------" << std::endl;
    }
}

void showHitCells(Ocean ocean){
    for(int x = 0; x < ocean.getNumberOfColumns(); x++){
        std::cout << "  |  " << x;
    };
    std::cout << std::endl << "--------------------------------------------------------------" << std::endl;
    std::string symbol;
    for(int y = 0; y < ocean.getNumberOfRows(); y++){
        std:: cout << y << " | ";
        for(int x = 0; x < ocean.getNumberOfColumns(); x++){
            symbol = ((ocean.getCell(x,y).getIsHit())? "o" : " ");
            std::cout << " " << symbol << "  | ";
        }
        std::cout << std::endl << "--------------------------------------------------------------" << std::endl;
    }
}
