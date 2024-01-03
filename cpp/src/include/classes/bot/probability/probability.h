#ifndef PROBABILITY_H_
#define PROBABILITY_H_

#include <functional>
#include "../hunt_&_target/hunt_&_target.h"

/**
 * @class Probability
 * @brief Algoritmo che, nella fase di hunt, calcola la probabilità che una cella sia occupata dato lo stato della griglia e colpisce la cella con la probabilità maggiore.
 * Nella fase di target, calcola la probabilità delle celle adiacenti al target e colpisce quella più probabile.
 */
class Probability : public HuntAndTarget {

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
     * @brief Esegue la fase di caccia della strategia (colpisce la cella con la probabilità di essere occupata maggiore).
     */
    void hunt() override;

    /**
     * @brief Esegue la fase di targeting calcolando la probabilità delle celle adiacenti al target.
     * 
     * @return True se ha colpito un bersaglio presente nella lista, False se la lista non contiene bersagli validi.
     */
    bool target() override;

    /**
     * @brief Aggiunge la cella con le coordinate x,y alla lista dei bersagli.
     * 
     * @param x Coordinata x della cella.
     * @param y Coordinata y della cella.
     */
    void addToTargets(int x, int y) override;

private:
    /**
     * @brief Individua se il bersaglio precedente risulta orizzontale o verticale rispetto a quello attuale.
     * 
     * @return True se orizzontale, false se verticale.
     */
    bool isPrevTargetHorizontal();

    /**
     * @brief Rimuove dalla lista dei bersagli le celle appartenenti all'ultima nave distrutta.
     */
    void emptyTargetList();

    int number_of_ships_;   ///< Numero di navi della flotta.
};

#endif
