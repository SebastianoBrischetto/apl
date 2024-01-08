#include <iostream>
#include <ctime>
#include "../game_elements/include_game_elements.h"
#include "../bot/include_bots.h"

void showCells(Ocean& ocean){
    //riga di separazione
    std::string end_rows = "---";
    //prima griglia
    for(int x = 0; x < ocean.getNumberOfColumns(); x++){
        std::cout << "  |  " << x;
        end_rows += "------";
    };

    //seconda griglia
    std::cout << "              ";
    for(int x = 0; x < ocean.getNumberOfColumns(); x++){
        std::cout << "  |  " << x;
    };

    //fine prima riga
    std::cout << std::endl << end_rows << "           " << end_rows << std::endl;

    //simbolo da stampare
    std::string symbol;

    //per ogni riga
    for(int y = 0; y < ocean.getNumberOfRows(); y++){
        std:: cout << y << " | ";
        //per ogni colonna (prima griglia)
        for(int x = 0; x < ocean.getNumberOfColumns(); x++){

            //stampa la probabilita
            std::cout<< "\033[1m";
            symbol = std::to_string(ocean.getCell(x, y).getOccupiedProbability());
            if(ocean.getCell(x, y).getOccupiedProbability()/10 == 0 && ocean.getCell(x,y).getOccupiedProbability() >= 0){
                symbol += " ";
            }
            std::cout << " " << symbol << " \033[0m| ";
        }

        std::cout << "          ";
        std:: cout << y << " | ";
        //per ogni colonna (seconda griglia)
        for(int x = 0; x < ocean.getNumberOfColumns(); x++){
            std::cout<< "\033[1m";
            symbol = (ocean.getCell(x,y).getIsOccupied())? "\033[34m0" : " ";
            symbol = ocean.getCell(x,y).getIsHit() ? ocean.getCell(x,y).getIsOccupied() ? "\033[31m\u00D8" : "\033[33m/" : symbol ;
            std::cout << " " << symbol << "  \033[0m| ";
        }

        //fine riga
        std::cout << std::endl << end_rows << "          " << end_rows << std::endl;
    }
}

void tryGame(int columns, int rows, int destroyers, int sumbarines, int cruisers, int battleships, int carriers, BotType type_of_bot) {
    int num_games = 0;
    int total_rounds = 0;
    while(true){
        int current_average_rounds = 0;
        if(num_games > 0){
            current_average_rounds = total_rounds / num_games;
        }
        num_games++;

        // Init Game board
        Ocean ocean(columns, rows);
        Fleet fleet(ocean);
        fleet.addToFleet(DESTROYER, destroyers, ocean);
        fleet.addToFleet(SUBMARINE, sumbarines, ocean);
        fleet.addToFleet(CRUISER, cruisers, ocean);
        fleet.addToFleet(BATTLESHIP, battleships, ocean);
        fleet.addToFleet(CARRIER, carriers, ocean);

        // Init bot
        BotAlgorithm* bot = nullptr;  
        switch(type_of_bot){
            case RANDOM:
                bot = new Random(ocean, fleet);
                break;
            case HUNT_AND_TARGET:
                bot = new HuntAndTarget(ocean, fleet);
                break;
            case PARITY:
                bot = new Parity(ocean, fleet);
                break;
            case PROBABILITY:
                bot = new Probability(ocean, fleet);
                break;
        }

        // Effettua una mossa finche rimangono navi
        while(!fleet.getIsFleetDestroyed()){
            bot->doMove();
            std::system("clear");
            showCells(ocean);
            // Statistiche partita
            std::cout << "ROUND: " << bot->getCounter() << std::endl;
            std::cout << "Numero navi rimaste: " << std::endl;
            std::cout << " - " << "Destroyers: " << fleet.getNumberOfDestroyers() << std::endl;
            std::cout << " - " << "Submarines & Cruisers: " << fleet.getNumberOfSubmarinesAndCruisers() << std::endl;
            std::cout << " - " << "Battleships: " << fleet.getNumberOfBattleships() << std::endl;
            std::cout << " - " << "Carriers: " << fleet.getNumberOfCarriers() << std::endl;
            std::cout << "Ultima cella colpita {" << bot->getLastHitX() << "," << bot->getLastHitY() << "}" << std::endl;
            std::cout << "Numero partite: " << num_games << std::endl;
            std::cout << "Media round: " << current_average_rounds << std::endl;
            std::cout << "Press any button to do next move, ctrl+c to exit";
            std::cin.ignore();
        };
        std::cout << "Partita finita" << std::endl;
        total_rounds += bot->getCounter();
        delete bot;
        std::cout << "Press any button to restart, ctrl+c to exit" << std::endl;
        std::cin.ignore();
    }
}