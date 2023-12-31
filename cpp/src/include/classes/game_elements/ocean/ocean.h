#ifndef OCEAN_H_
#define OCEAN_H_

#include <vector>
#include "../cell/cell.h"

// Direzione del piazzamento delle navi
enum Direction {
    UP,     ///< Verso nord (0).
    RIGHT,  ///< Verso est (1).
    DOWN,   ///< Verso sud (2).
    LEFT    ///< Verso ovest (3).
};

/**
 * @class Ocean
 * @brief Rappresenta la griglia composta dalle celle.
 */
class Ocean {

public:
    /**
     * @brief Inizializza un oggetto ocean composto da rows_ * columns_ celle.
     * 
     * @param columns Numero di colonne della griglia.
     * @param rows Numero di righe della griglia.
     */
    Ocean(int columns, int rows);

    /**
     * @brief Ritorna il numero di righe della griglia.
     * 
     * @return Numero di righe.
     */
    int getNumberOfRows() const;

    /**
     * @brief Ritorna il numero di colonne della griglia.
     * 
     * @return Numero di colonne.
     */
    int getNumberOfColumns() const;

    /**
     * @brief Indica se la coppia di coordinate (x, y) è valida (non fuori dalla griglia).
     * 
     * @param x Coordinata x.
     * @param y Coordinata y.
     * 
     * @return True se le coordinate sono valide, false altrimenti.
     */
    bool areCoordinatesValid(int x, int y) const;

    /**
     * @brief Ritorna il riferimento alla cella di posizione (x, y).
     *
     * @param x Coordinata x della cella.
     * @param y Coordinata y della cella.
     *
     * @throw std::runtime_error Se le coordinate fornite sono fuori dalla griglia.
     */
    Cell& getCell(int x, int y);

    /**
     * @brief Ritorna il riferimento alla cella con la probabilità massima che sia occupata; in caso di celle con la stessa probabilità,
     * ne viene scelta una in modo casuale.
     *
     * @return Riferimento alla cella con la probabilità massima.
     */
    Cell& getMaxProbabilityCell();

    /**
     * @brief Rileva se un'area della griglia risulta occupata.
     * 
     * @param init_x Coordinata x da cui iniziare.
     * @param init_y Coordinata y da cui iniziare.
     * @param direction Direzione verso la quale effettuare il controllo.
     * @param length Numero di celle da controllare.
     *
     * @return True se lo spazio è occupato, false altrimenti.
     */
    bool isSpaceOccupied(int init_x, int init_y, Direction direction, int length);

    /**
     * @brief Ritorno il numero di celle valide lungo una direzione.
     * per modalita non target le celle valide sono solo quelle non colpite.
     * per modalita target le celle valide sono quelle non colpite e quelle colpite ed affondate.
     * 
     * @param init_x Coordinata x da cui iniziare.
     * @param init_y Coordinata y da cui iniziare.
     * @param direction Direzione verso la quale effettuare il controllo.
     * @param length Numero di celle da controllare.
     * @param target Flag che indica se valutare le celle in modalita target o non.
     *
     * @return Numero di celle valide lungo la direzione scelta.
     */
    int getMaxUnhitSpace(int init_x, int init_y, Direction direction, int length, bool target = false);

    // REFACTOR - usa una cella come posizione iniziale e ritorna il riferimento alla cella invece di aggiornare le coordinate (x_reference, y_reference)
    /**
     * @brief Modifica le coordinate fornite in modo da spostarsi nella direzione richiesta.
     *
     * @param x_init_value Valore iniziale per x.
     * @param y_init_value Valore iniziale per y.
     * @param x_reference Riferimento alla coordinata x da aggiornare.
     * @param y_reference Riferimento alla coordinata y da aggiornare.
     * @param increment Valore per la quale incrementare.
     * @param direction Direzione verso dove aggiornare le coordinate.
     */
    static void updateCoordinates(int x_init_value, int y_init_value, int& x_reference, int& y_reference, int increment, Direction direction);

    /**
     * @brief Setta la probabilità che una cella sia occupata per ognuna delle celle non colpite che formano la griglia.
     *
     * @param destroyers Numero di destroyers (navi di lunghezza = 2) rimanenti.
     * @param submarines_and_cruisers Numero di submarines e cruisers (navi di lunghezza = 3) rimanenti.
     * @param battleships Numero di battleships (navi di lunghezza = 4) rimanenti.
     * @param carriers Numero di carriers (navi di lunghezza = 5) rimanenti.
     */
    void calcOceanProbability(int destroyers, int submarines_and_cruisers, int battleships, int carriers);

    /**
     * @brief Resetta la probabilità di ogni cella dell'oceano.
     */
    void resetOceanProbability();

    // REFACTOR - viene passato il riferimento della cella iniziale invece delle coordinate
    /**
     * @brief Calcola la probabilita delle celle lungo la direzione richiesta in base al numero di navi fornite.
     *
     * @param init_x Coordinata x della cella iniziale.
     * @param init_y Coordinata y della cella iniziale.
     * @param direction Direzione celle adiacenti.
     * @param destroyers Numero di destroyers (navi di lunghezza = 2) rimanenti.
     * @param submarines_and_cruisers Numero di submarines e cruisers (navi di lunghezza = 3) rimanenti.
     * @param battleships Numero di battleships (navi di lunghezza = 4) rimanenti.
     * @param carriers Numero di carriers (navi di lunghezza = 5) rimanenti.
     * 
     * @param target Flag che indica se calcolare la probabilità per lo scenario targeting o meno.
     * @param bonus Bonus da applicare durante il calcolo della probabilità (usato per lo scenario targeting).
     */
    void calcDirectionProbability(  int init_x, int init_y, Direction direction, 
                                    int destroyers, int submarines_and_cruisers, int battleships, int carriers, 
                                    bool target = false, int bonus = 0);
    
    // REFACTOR - viene passato il riferimento della cella target iniziale invece delle coordinate
    /**
     * @brief Calcola le probabilità lungo le quattro direzioni rispetto ad un target.
     *
     * @param target_x Coordinata x della cella target.
     * @param target_y Coordinata y della cella target.
     * @param destroyers Numero di destroyers (navi di lunghezza = 2) rimanenti.
     * @param submarines_and_cruisers Numero di submarines e cruisers (navi di lunghezza = 3) rimanenti.
     * @param battleships Numero di battleships (navi di lunghezza = 4) rimanenti.
     * @param carriers Numero di carriers (navi di lunghezza = 5) rimanenti.
     * 
     * @param vertical_bonus Bonus da applicare per le celle verticali a quella target.
     * @param horizontal_bonus Bonus da applicare per le celle orizzontali a quella target.
     */
    void calcTargetProbability( int target_x, int target_y, 
                                int destroyers, int submarines_and_cruisers, int battleships, int carriers, 
                                int vertical_bonus, int horizontal_bonus);

    /**
     * @brief Modifica il valore che verrà utilizzato per incrementare la probabilità che una cella risulti occupata.
     * 
     * @param probability Riferimento al valore da aggiornare.
     * @param index distanza rispetto alla cella dalla quale si sta calcolando la probabilita
     * @param destroyers Numero di destroyers (navi di lunghezza = 2) rimanenti.
     * @param submarines_and_cruisers Numero di submarines e cruisers (navi di lunghezza = 3) rimanenti.
     * @param battleships Numero di battleships (navi di lunghezza = 4) rimanenti.
     * @param carriers Numero di carriers (navi di lunghezza = 5) rimanenti.
     */
    void updateProbability(int& probability, int index, int destroyers, int submarines_and_cruisers, int battleships, int carriers, bool target = false);

private:
    int rows_;                   ///< Numero di righe della griglia.
    int columns_;                ///< Numero di colonne della griglia.
    std::vector<Cell> ocean_;    ///< Vettore contenente le celle che formano l'oceano.
};

#endif