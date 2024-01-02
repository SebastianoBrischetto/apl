#ifndef PROBABILITY_H_
#define PROBABILITY_H_

#include <functional>
#include "../hunt_&_target/hunt_&_target.h"

/**
 * @class Parity
 * @brief Algoritmo che nella fase di hunt calcola la probabilita che una cella sia occupata dato lo stato della griglia e colpisce la cella con la probabilita maggiore,
 * mentre nella fase di target calcola la probabilita delle celle adiacenti al target e colpisce quella piu probabile.
 */
class Probability: public HuntAndTarget{

public:
    /**
     * @brief Costruttore per il bot probability.
     * 
     * @param ocean Riferimento all'oceano nemico.
     * @param fleet Riferimento alla flotta nemica.
     */
    Probability(Ocean& ocean, Fleet& fleet);
    
protected:
    /**
     * @brief Esegue la fase di caccia della strategia (colpisce la cella con la probabilita di essere occupata maggiore).
     */
    void hunt() override;

    /**
     * @brief Esegue la fase di targeting calcolando la probabilita delle celle adiacenti al target.
     */
    void target() override;

    /**
     * @brief Aggiunge la cella con le coordinate x,y alla lista dei bersagli.
     * 
     * @param x cordinata x della cella.
     * @param y cordinata y della cella.
     */
    void addToTargets(int x, int y) override;
private:

    /**
     * @brief Individua se il bersaglio precedente sia orizzontale o verticale rispetto a quello attuale.
     * 
     * @return True se orizzontale, false se verticale
     */
    bool isPrevTargetHorizontal();

    /**
     * @brief Rimuove dalla lista dei bersagli le celle appartenenti all'ultima nave distrutta.
     */
    void emptyTargetList();

    int number_of_ships_;   ///< Numero di navi della flotta
};

#endif