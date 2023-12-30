#include <iostream>
#include <ctime>
#include "include/classes/fleet/fleet.h"
#include "include/classes/random/random.h"

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


    int columns = 10, rows = 10, destroyers = 5, sumbarines = 3;
    /*
    std::cout << "Inserisci il numero di colonne" << std::endl;
    std::cin >> columns;
    std::cout << "Inserisci il numero di righe" << std::endl;
    std::cin >> rows;
    std::cout << "Inserisci il numero di navi destroyer" << std::endl;
    std::cin >> destroyers;
    std::cout << "Inserisci il numero di navi sumbarine" << std::endl;
    std::cin >> sumbarines;
    */
    Ocean ocean = Ocean(columns, rows);
    Fleet fleet = Fleet(DESTROYER, destroyers, ocean);
    fleet.addToFleet(SUBMARINE, sumbarines, ocean);
    Random bot = Random(ocean);
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
    };
    std::system("clear");
    showCells(ocean);
    std::cout << "ROUND: " << counter << std::endl;
    std::cout << "Partita finita" << std::endl;
}