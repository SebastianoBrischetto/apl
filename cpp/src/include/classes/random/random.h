#ifndef RANDOM_H_
#define RANDOM_H_

#include "../bot_algorithm/bot_algorithm.h"

/**
 * @class Random
 * @brief Bot con mosse casuali.
 */
class Random : public BotAlgorithm{

public:
    /**
     * @brief Costruttore per il bot random.
     * 
     * @param ocean Riferimento all'oceano nemico.
     * @param fleet Riferimento alla flotta nemica.
     */
    Random(Ocean& ocean, Fleet& fleet);

    /**
     * @brief esegue la strategia del bot (colpisce casualmente).
     */
    void doMove() override;

    /**
     * @brief Colpisce in modo casuale l'oceano e aumenta il contatore in caso di mossa valida.
     */
    void hitRandomly();
};

#endif