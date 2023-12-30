#ifndef SHIP_H_
#define SHIP_H_
#include <functional>
#include "../ocean/ocean.h"

class Ship{
    public:
        /**
         * Costruttore della nave generica.
         * 
         * Inizializza un oggetto nave composta da "length" celle con la prima cella di posizione {init_x_cord, init_y_cord}
         * e le rimanenti in base alla direzione scelta, le celle vengono settate ad occupate.
         * 
         * @param init_x_cord coordinata x della prima cella
         * @param init_y_cord coordinata y della prima cella
         * @param direction direzione verso la quale la nave verra piazzata
         * @param length numero di celle di cui e composta la nave
         * @param ocean riferimento all'oceano alla quale la nave verra associata
         * 
         * @throw se l'area della griglia dove si vuole piazzare la nave e gia occupata
         */
        Ship(int init_x_cord, int init_y_cord, Direction direction, int length, Ocean& ocean);

        //Torna il numero di celle che formano la nave
        int getLength();
        //Torna un bool che indica se la nave e stata affondata (true) o meno
        bool getIsSunk();
        /**
         * Torna il riferimento alla cella index-esima che forma la nave
         * 
         * @param index indice alla cella della nave alla quale si vuole accedere
         * 
         * @throw se si prova ad accedere ad una cella non associata alla nave
         */
        Cell& getPiece(int index);

    private:
        int length_;
        bool is_sunk_;
        Ocean& ocean_;
        std::vector<std::reference_wrapper<Cell>> ship_;
};

#endif