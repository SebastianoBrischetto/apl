#ifndef OCEAN_H_
#define OCEAN_H_
#include <vector>
#include "../cell/cell.h"

//Direzione piazzamento navi
enum Direction{
    UP,     //0
    RIGHT,  //1
    DOWN,   //2
    LEFT    //3
};

class Ocean{
    public:
        /**
         * Costruttore della griglia oceano.
         * 
         * Inizializza un oggetto oceano composto da un numero dim=rows_ * columns_ di oggetti cella
         * 
         * @param columns numero di colonne della griglia
         * @param rows numero di righe della griglia
         */
        Ocean(int columns, int rows);

        /**
         * Rileva se un'area della griglia risulta libera o meno
         * 
         * @param init_x_cord coordinata x da dove iniziare il controllo
         * @param init_y_cord coordinata y da dove iniziare il controllo
         * @param direction direzione verso la quale effettuare il controllo
         * @param length numero di celle da controllare
         * 
         * @return bool indica se lo spazio e libero (true) o occupato (false)
         */
        bool isSpaceOccupied(int init_x_cord, int init_y_cord, Direction direction, int length);

        //Torna il numero di righe
        int getNumberOfRows();
        //Torna il numero di colonne
        int getNumberOfColumns();
        /**
         * Torna la cella di posizione {x,y}
         * 
         * @param x coordinata x della cella
         * @param y coordinata y della cella
         * 
         * @throw se le coordinate fornite sono fuori i limiti della griglia
         */
        Cell& getCell(int x, int y);
        
    private:
        int rows_;
        int columns_;
        std::vector<Cell> ocean_;
};

#endif