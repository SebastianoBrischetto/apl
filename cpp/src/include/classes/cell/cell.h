#ifndef CELL_H_
#define CELL_H_

#include <stdexcept>

/**
 * @class Cell
 * @brief Rappresenta una cella nella griglia(ocean).
 */

class Cell{

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
     * @brief Ritorna un booleano che indica se la cella e stata colpita o meno.
     * 
     * @return True se la cella e colpita, False in caso contrario.
     */
    bool getIsHit() const;

    /**
     * @brief Ritorna un booleano che indica se la cella risulta occupata.
     * 
     * @return True se la cella e occupata, False in caso contrario.
     */
    bool getIsOccupied() const;

    /**
     * @brief Ritorna la probabilita che la cella risulti occupata.
     * 
     * @return Probabilita.
     */
    int getOccupiedProbability() const;

    /**
     * @brief Setta lo stato della cella a colpito.
     * 
     * @throw std::runtime_error se la cella e gia stata colpita.
     */
    void setIsHit();

    /**
     * @brief Setta lo stato della cella a occupato.
     * 
     * @throw std::runtime_error se la cella e gia occupata.
     */
    void setIsOccupied();

    /**
     * @brief Aumenta la probabilita della cella di una determinata quantita.
     * 
     * @param n Quantita dell'aumento.
     */
    void incraseOccupiedProbability(int n);

    /**
     * @brief Resetta la probabilita della cella a 0.
     */
    void resetOccupiedProbability();

private:
    int x_cord_;                ///< coordinata x della cella.
    int y_cord_;                ///< coordinata y della cella.
    bool is_hit_;               ///< indica se la cella e stata colpita.
    bool is_occupied_;          ///< indica se la cella e occupata.
    int occupied_probability_;  ///< probabilita che la cella risulta occupata.
};

#endif