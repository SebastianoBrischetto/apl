#ifndef CELL_H_
#define CELL_H_

#include <stdexcept>

/**
 * @class Cell
 * @brief Rappresenta una cella nella griglia (oceano).
 */

class Cell {
public:
    /**
     * @brief Inizializza un oggetto cella con le coordinate {x, y} e imposta is_hit_ e is_occupied a false.
     * 
     * @param init_x_coord coordinata sull'asse x.
     * @param init_y_coord coordinata sull'asse y.
     */
    Cell(int init_x_coord, int init_y_coord);

    /**
     * @brief Ritorna la coordinata x della cella.
     * 
     * @return Coordinata x.
     */
    int getXCoord() const;

    /**
     * @brief Ritorna la coordinata y della cella.
     * 
     * @return Coordinata y.
     */
    int getYCoord() const;

    /**
     * @brief Ritorna un booleano che indica se la cella è stata colpita o meno.
     * 
     * @return True se la cella è stata colpita, False altrimenti.
     */
    bool getIsHit() const;

    /**
     * @brief Ritorna un booleano che indica se la cella è occupata.
     * 
     * @return True se la cella è occupata, False altrimenti.
     */
    bool getIsOccupied() const;

    /**
     * @brief Ritorna la probabilità che la cella sia occupata.
     * 
     * @return Probabilità.
     */
    int getOccupiedProbability() const;

    /**
     * @brief Imposta lo stato della cella a "colpita".
     * 
     * @throw std::runtime_error se la cella è già stata colpita.
     */
    void setIsHit();

    /**
     * @brief Imposta lo stato della cella a "occupata".
     * 
     * @throw std::runtime_error se la cella è già occupata.
     */
    void setIsOccupied();

    /**
     * @brief Aumenta la probabilità che la cella sia occupata di una determinata quantità.
     * 
     * @param n Quantità di aumento.
     */
    void increaseOccupiedProbability(int n);

    /**
     * @brief Resetta la probabilità che la cella sia occupata a 0.
     */
    void resetOccupiedProbability();

private:
    int x_coord_;                ///< Coordinata x della cella.
    int y_coord_;                ///< Coordinata y della cella.
    bool is_hit_;                ///< Indica se la cella è stata colpita.
    bool is_occupied_;           ///< Indica se la cella è occupata.
    int occupied_probability_;   ///< Probabilità che la cella sia occupata.
};

#endif