#include <iostream>
#include <ctime>
#include "include/classes/fleet/fleet.h"
#include "include/classes/random/random.h"
#include "include/classes/hunt_&_target/hunt_&_target.h"

void showCells(Ocean& ocean){
    for(int x = 0; x < ocean.getNumberOfColumns(); x++){
        std::cout << "  |  " << x;
    };
    std::cout << std::endl << "--------------------------------------------------------------" << std::endl;
    std::string symbol;
    for(int y = 0; y < ocean.getNumberOfRows(); y++){
        std:: cout << y << " | ";
        for(int x = 0; x < ocean.getNumberOfColumns(); x++){
            std::cout<< "\033[1m";
            symbol = " ";
            //symbol = (ocean.getCell(x,y).getIsOccupied())? "\033[34m0" : symbol;
            symbol = ocean.getCell(x,y).getIsHit() ? ocean.getCell(x,y).getIsOccupied() ? "\033[31m\u00D8" : "\033[33m/" : symbol ;
            std::cout << " " << symbol << "  \033[0m| ";
        }
        std::cout << std::endl << "--------------------------------------------------------------" << std::endl;
    }
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));


    int columns = 10, rows = 10, destroyers = 1, sumbarines = 1, cruisers = 1, battleships = 1, carriers = 1;
    Ocean ocean = Ocean(columns, rows);
    Fleet fleet = Fleet(DESTROYER, destroyers, ocean);
    fleet.addToFleet(SUBMARINE, sumbarines, ocean);
    fleet.addToFleet(CRUISER, cruisers, ocean);
    fleet.addToFleet(BATTLESHIP, battleships, ocean);
    fleet.addToFleet(CARRIER, carriers, ocean);
    HuntAndSearch bot = HuntAndSearch(ocean);
    bool game_over = false;
    int x;
    int y;
    int counter = 0;
    showCells(ocean);
    std::cout << "ROUND: " << counter << std::endl;
    while(!game_over){
        std::system("clear");
        showCells(ocean);
        std::cout << "ROUND: " << ++counter << std::endl;
        /*
        std::cout << std::endl << "Inserisci la coordinata x da colpire: ";
        std::cin >> x;
        std::cout << "Inserisci la coordinata y da colpire: ";
        std::cin >> y;
        */
        bot.doMove();
        std::system("sleep 0.1");
        game_over = fleet.getIsFleetDestroyed();
        if((counter >= 120)){
            break;
        }
    };
    std::system("clear");
    showCells(ocean);
    std::cout << "ROUND: " << counter << std::endl;
    std::cout << "Partita finita" << std::endl;
}