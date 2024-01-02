#ifndef SHIP_H_
#define SHIP_H_

#include <functional>
#include "../ocean/ocean.h"

/**
 * @class Ocean
 * @brief Rappresenta una nave all'interno della griglia.
 */
class Ship{

public:
    /**
     * Costruttore della nave generica.
     * 
     * Inizializza un oggetto nave composta da "length" celle con la prima cella di posizione {init_x_cord, init_y_cord}
     * e le rimanenti in base alla direzione scelta, le celle vengono settate come occupate.
     * 
     * @param init_x_cord coordinata x della prima cella
     * @param init_y_cord coordinata y della prima cella
     * @param direction direzione verso la quale la nave verra piazzata
     * @param length numero di celle di cui e composta la nave
     * @param ocean riferimento all'oceano alla quale la nave verra associata
     * 
     * @throw std::runtime_error se l'area della griglia dove si vuole piazzare la nave e gia occupata
     */
    Ship(int init_x_cord, int init_y_cord, Direction direction, int length, Ocean& ocean);

    /**
     * Costruttore default
     */
    Ship(Ocean& ocean);

    /**
     * @brief Torna il numero di celle che formano la nave.
     * 
     * @return Numero di celle che compongono la nave.
     */
    int getLength() const;

        /**
     * @brief Torna il riferimento all'oceano dove si trova la nave.
     * 
     * @return Riferimento all'oggetto ocean.
     */
    Ocean& getOcean() const;
    
    /**
     * Torna il riferimento alla cella index-esima che forma la nave
     * 
     * @param index indice alla cella della nave alla quale si vuole accedere
     * 
     * @throw std::runtime_error se si prova ad accedere ad una cella non associata alla nave
     */
    Cell& getPiece(int index) const;

    /**
     * @brief Torna un booleano che indica se la nave è stata affondata o meno.
     * 
     * @return True se la nave è affondata, False in caso contrario.
     */
    bool isShipSunk();

    /**
     * @brief Copia i dati di una nave.
     * 
     * @return Ritorna il riferimento alla copia.
     */
    Ship& operator=(const Ship& original);


private:
    int length_;                                        ///< Numero di celle che formano la nave.
    Ocean& ocean_;                                      ///< Riferimento all'oceano associato alla nave.
    std::vector<std::reference_wrapper<Cell>> ship_;    ///< Vettore di celle che compongono la nave.
};

#endif