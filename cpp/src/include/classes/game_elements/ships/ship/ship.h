#ifndef SHIP_H_
#define SHIP_H_

#include <functional>
#include "../../ocean/ocean.h"

/**
 * @class Ship
 * @brief Rappresenta una nave all'interno della griglia.
 */
class Ship {

public:
    /**
     * @brief Costruttore per la nave generica.
     * 
     * Inizializza un oggetto nave composta da "length" celle con la prima cella in posizione {init_x_coord, init_y_coord}
     * e le restanti in base alla direzione scelta; le celle vengono impostate come occupate.
     * 
     * @param init_x_coord Coordinata X della prima cella.
     * @param init_y_coord Coordinata Y della prima cella.
     * @param direction Direzione nella quale verrà posizionata la nave.
     * @param length Numero di celle che compongono la nave.
     * @param ocean Riferimento all'oceano a cui verrà associata la nave.
     * 
     * @throw std::runtime_error Se l'area della griglia dove si vuole piazzare la nave è già occupata.
     */
    Ship(int init_x_coord, int init_y_coord, Direction direction, int length, Ocean& ocean);

    /**
     * @brief Costruttore di default.
     */
    Ship(Ocean& ocean);

    /**
     * @brief Ottieni il numero di celle che compongono la nave.
     * 
     * @return Numero di celle che compongono la nave.
     */
    int getLength() const;

    /**
     * @brief Ottieni il riferimento all'oceano in cui si trova la nave.
     * 
     * @return Riferimento all'oggetto ocean.
     */
    Ocean& getOcean() const;

    /**
     * @brief Ottieni il riferimento alla cella in posizione index della nave.
     * 
     * @param index Indice della cella della nave alla quale si vuole accedere
     * 
     * @throw std::runtime_error Se si prova ad accedere a una cella non associata alla nave.
     */
    Cell& getShipPiece(int index) const;

    /**
     * @brief Verifica se la nave è affondata.
     * 
     * @return True se la nave è affondata, False altrimenti.
     */
    bool isShipSunk();

    /**
     * @brief Copia i dati di una nave.
     * 
     * @return Ritorna il riferimento alla copia.
     */
    Ship& operator=(const Ship& original);

private:
    int length_;                                        ///< Numero di celle che compongono la nave.
    Ocean& ocean_;                                      ///< Riferimento all'oceano associato alla nave.
    std::vector<std::reference_wrapper<Cell>> ship_;    ///< Vettore di celle che compongono la nave.
};

#endif