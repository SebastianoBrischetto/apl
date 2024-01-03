#include <iostream>
#include <ctime>
#include "include/classes/fleet/fleet.h"
#include "include/classes/random/random.h"
#include "include/classes/hunt_&_target/hunt_&_target.h"
#include "include/classes/parity/parity.h"
#include "include/classes/probability/probability.h"

void showCells(Ocean& ocean){
    std::string end_rows = "---";
    for(int x = 0; x < ocean.getNumberOfColumns(); x++){
        std::cout << "  |  " << x;
        end_rows += "------";
    };
    std::cout << "              ";
    for(int x = 0; x < ocean.getNumberOfColumns(); x++){
        std::cout << "  |  " << x;
    };

    std::cout << std::endl << end_rows << std::endl;
    std::string symbol;
    for(int y = 0; y < ocean.getNumberOfRows(); y++){
        std:: cout << y << " | ";
        for(int x = 0; x < ocean.getNumberOfColumns(); x++){
            std::cout<< "\033[1m";
            symbol = " ";
            symbol = (ocean.getCell(x,y).getIsOccupied())? "\033[34m0" : symbol;
            symbol = ocean.getCell(x,y).getIsHit() ? ocean.getCell(x,y).getIsOccupied() ? "\033[31m\u00D8" : "\033[33m/" : symbol ;
            symbol = std::to_string(ocean.getCell(x, y).getOccupiedProbability());
            if(ocean.getCell(x, y).getOccupiedProbability()/10 != 0 || ocean.getCell(x,y).getOccupiedProbability() < 0){
                std::cout << " " << symbol << " \033[0m| ";
                continue;
            }
            std::cout << " " << symbol << "  \033[0m| ";
        }

        std::cout << "          ";
        std:: cout << y << " | ";
        for(int x = 0; x < ocean.getNumberOfColumns(); x++){
            std::cout<< "\033[1m";
            symbol = " ";
            symbol = (ocean.getCell(x,y).getIsOccupied())? "\033[34m0" : symbol;
            symbol = ocean.getCell(x,y).getIsHit() ? ocean.getCell(x,y).getIsOccupied() ? "\033[31m\u00D8" : "\033[33m/" : symbol ;
            std::cout << " " << symbol << "  \033[0m| ";
        }
        std::cout << std::endl << end_rows << "          " << end_rows << std::endl;
    }
}

int main() {
    //init board
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    int columns = 10, rows = 10, destroyers = 1, sumbarines = 1, cruisers = 1, battleships = 1, carriers = 1;
    bool run = true;
    int num_games = 0;
    int total_rounds = 0;
    while(run){
    int current_average_rounds = 0;
    if(num_games > 0){
        current_average_rounds = total_rounds / num_games;
    }
    num_games++;
    Ocean ocean(columns, rows);
    Fleet fleet(DESTROYER, destroyers, ocean);
    fleet.addToFleet(SUBMARINE, sumbarines, ocean);
    fleet.addToFleet(CRUISER, cruisers, ocean);
    fleet.addToFleet(BATTLESHIP, battleships, ocean);
    fleet.addToFleet(CARRIER, carriers, ocean);

    //bot
    Probability bot(ocean, fleet);

    //game status
    bool game_over = false; 
    int x, y;

    while(!fleet.getIsFleetDestroyed()){
        bot.doMove();
        /*
        std::cout << "coordinata x: ";
        std::cin >> x;
        std::cout << "coordinata y: ";
        std::cin >> y;
        ocean.getCell(x, y).setIsHit();
        */

        std::system("clear");
        showCells(ocean);
        std::cout << "ROUND: " << bot.getCounter() << std::endl;
        std::cout << "Numero navi rimaste: " << std::endl;
        std::cout << " - " << "Destroyers: " << fleet.getNumberOfDestroyers() << std::endl;
        std::cout << " - " << "Submarines & Cruisers: " << fleet.getNumberOfSubmarinesAndCruisers() << std::endl;
        std::cout << " - " << "Battleships: " << fleet.getNumberOfBattleships() << std::endl;
        std::cout << " - " << "Carriers: " << fleet.getNumberOfCarriers() << std::endl;
        std::cout << "cella con probabilita max: {" << ocean.getMaxProbabilityCell().getXCord() << "," << ocean.getMaxProbabilityCell().getYCord() << "}" << std::endl;
        std::cout << "Numero partite: " << num_games << std::endl;
        std::cout << "Media round: " << current_average_rounds << std::endl;
        if((bot.getCounter() >= 100)){ break; }

        //std::system("sleep 0.05");
        //std::cout << "Press any button to do next move";
        //std::cin.ignore();
    };
    std::cout << "Partita finita" << std::endl;
    total_rounds += bot.getCounter();
    std::system("sleep 1");
    //std::cin >> run;
    }
}