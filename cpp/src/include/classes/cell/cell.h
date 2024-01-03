#ifndef CELL_H_
#define CELL_H_

#include <stdexcept>

/**
 * @class Cell
 * @brief Rappresenta una cella nella griglia (ocean).
 */

class Cell {
public:
    /**
     * @brief Inizializza un oggetto cella con le coordinate {x, y} e setta is_hit_ e is_occupied a false
     * 
     * @param init_x_cord cordinata asse x
     * @param init_y_cord cordinata asse y
     */
    Cell(int init_x_cord, int init_y_cord);

    /**
     * @brief Ritorna la coordinata x della cella.
     * 
     * @return coordinata x.
     */
    int getXCord() const;

    /**
     * @brief Ritorna la coordinata y della cella.
     * 
     * @return coordinata y.
     */
    int getYCord() const;

    /**
     * @brief Ritorna un booleano che indica se la cella è stata colpita o meno.
     * 
     * @return True se la cella è colpita, False in caso contrario.
     */
    bool getIsHit() const;

    /**
     * @brief Ritorna un booleano che indica se la cella risulta occupata.
     * 
     * @return True se la cella è occupata, False in caso contrario.
     */
    bool getIsOccupied() const;

    /**
     * @brief Ritorna la probabilità che la cella risulti occupata.
     * 
     * @return Probabilità.
     */
    int getOccupiedProbability() const;

    /**
     * @brief Setta lo stato della cella a colpito.
     * 
     * @throw std::runtime_error se la cella è già stata colpita.
     */
    void setIsHit();

    /**
     * @brief Setta lo stato della cella a occupato.
     * 
     * @throw std::runtime_error se la cella è già occupata.
     */
    void setIsOccupied();

    /**
     * @brief Aumenta la probabilità della cella di una determinata quantità.
     * 
     * @param n Quantità dell'aumento.
     */
    void increaseOccupiedProbability(int n);

    /**
     * @brief Resetta la probabilità della cella a 0.
     */
    void resetOccupiedProbability();

private:
    int x_cord_;                ///< coordinata x della cella.
    int y_cord_;                ///< coordinata y della cella.
    bool is_hit_;               ///< indica se la cella è stata colpita.
    bool is_occupied_;          ///< indica se la cella è occupata.
    int occupied_probability_;  ///< probabilità che la cella risulti occupata.
};

#endif