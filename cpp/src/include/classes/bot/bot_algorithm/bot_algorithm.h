#ifndef BOT_ALGORITHM_H_
#define BOT_ALGORITHM_H_

#include "../../game_elements/include_game_elements.h"

// Tipi di bot
enum BotType{
    RANDOM,             ///< 0.
    HUNT_AND_TARGET,    ///< 1.
    PARITY,             ///< 2.
    PROBABILITY         ///< 3.
};

/**
 * @class BotAlgorithm
 * @brief Classe astratta per il bot di Battaglia Navale.
 */
class BotAlgorithm {

public:
    /**
     * @brief Costruttore per il bot.
     * 
     * @param ocean Riferimento all'oceano nemico.
     * @param fleet Riferimento alla flotta nemica.
     */
    BotAlgorithm(Ocean& ocean, Fleet& fleet);

    /**
     * @brief Metodo astratto per permettere al bot di effettuare un'azione.
     */
    virtual void doMove() = 0;

    /**
     * @brief Ritorna il numero di mosse effettuate dal bot.
     */
    int getCounter();

    /**
     * @brief Ritorna la coordinata x dell'ultima cella colpita.
     * 
     * @return Coordinata X.
     */
    int getLastHitX();

    /**
     * @brief Ritorna la coordinata y dell'ultima cella colpita.
     * 
     * @return Coordinata Y.
     */
    int getLastHitY();
    
    // REFACTOR - viene passato il riferimento della cella target iniziale invece delle coordinate
    /**
     * @brief Effettua un attacco alle coordinate passate e notifica la flotta nemica di aggiornare il proprio stato.
     * 
     * @param x Coordinata x del colpo.
     * @param y Coordinata y del colpo.
     * 
     * @return True se il colpo ha avuto successo, false in caso contrario.
     */
    bool hitAndNotify(int x, int y);


protected:
    int last_hit_x_ ;
    int last_hit_y_ ;
    int columns_;   ///< Numero di colonne della griglia nemica.
    int rows_;      ///< Numero di righe della griglia nemica.
    int counter_;   ///< Numero di mosse effettuate dal bot.
    Ocean& ocean_;  ///< Riferimento all'oceano nemico.
    Fleet& fleet_;  ///< Riferimento alla flotta nemica.
};

#endif