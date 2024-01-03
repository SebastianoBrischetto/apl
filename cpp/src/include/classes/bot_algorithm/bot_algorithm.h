#ifndef BOT_ALGORITHM_H_
#define BOT_ALGORITHM_H_

#include "../fleet/fleet.h"

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
     * @brief Effettua un attacco alle coordinate passate e notifica la flotta nemica di aggiornare il proprio stato.
     * 
     * @param x Coordinata x del colpo.
     * @param y Coordinata y del colpo.
     * 
     * @return True se il colpo ha avuto successo, false in caso contrario.
     */
    bool hitAndNotify(int x, int y);

protected:
    int columns_;   ///< Numero di colonne della griglia nemica.
    int rows_;      ///< Numero di righe della griglia nemica.
    int counter_;   ///< Numero di mosse effettuate dal bot.
    Ocean& ocean_;  ///< Riferimento all'oceano nemico.
    Fleet& fleet_;  ///< Riferimento alla flotta nemica.
};

#endif