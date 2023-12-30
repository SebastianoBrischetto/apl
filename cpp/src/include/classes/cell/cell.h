#ifndef CELL_H_
#define CELL_H_
#include <stdexcept>

class Cell{
    public:
        /**
         * Costruttore della cella.
         * 
         * Inizializza un oggetto cella con le coordinate {x, y} e setta is_hit_ e is_occupied a false
         * 
         * @param init_x_cord cordinata asse x
         * @param init_y_cord cordinata asse y
         */
        Cell(int init_x_cord, int init_y_cord);


        //Torna la coordinata x
        int getXCord();
        //Torna la coordinata y
        int getYCord();
        //Torna un bool che indica se la cella e stata colpita o meno
        bool getIsHit();
        //Torna un bool che indica se la cella e occupata o meno
        bool getIsOccupied();

        /**
         * Setta la cella come colpita.
         * 
         * @throw se la cella e gia stata colpita
         */
        void setIsHit();


        /**
         * Setta la cella come occupata.
         * 
         * @throw se la cella e gia occupata
         */
        void setIsOccupied();

    private:
        int x_cord_;
        int y_cord_;
        bool is_hit_;
        bool is_occupied_;
};

#endif