#ifndef PARITY_H_
#define PARITY_H_

#include "../hunt_&_target/hunt_&_target.h"

/**
 * @class Parity
 * @brief Algoritmo che esegue una prima fase di caccia colpendo le celle con la stessa parita, e dopo aver trovato un bersaglio colpisce intorno ad esso.
 */
class Parity: public HuntAndTarget{

public:
    /**
     * @brief Costruttore per il bot parity.
     * 
     * @param ocean Riferimento all'oceano nemico.
     * @param fleet Riferimento alla flotta nemica.
     */
    Parity(Ocean& ocean, Fleet& fleet);
    
protected:
    /**
     * @brief Esegue la fase di caccia della strategia (colpisce le celle che hanno le cordinate con la stessa parita).
     */
    void hunt() override;
};

#endif