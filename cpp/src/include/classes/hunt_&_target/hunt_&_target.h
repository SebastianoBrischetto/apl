#ifndef HUNT_AND_TARGET_H_
#define HUNT_AND_TARGET_H_

#include <deque>
#include <functional>
#include "../bot_algorithm/bot_algorithm.h"

/**
 * @class HuntAndTarget
 * @brief Algoritmo che esegue una prima fase di caccia colpendo in modo casuale, e dopo aver trovato un bersaglio colpisce intorno ad esso.
 */
class HuntAndTarget : public BotAlgorithm{

public:
    /**
     * @brief Costruttore per il bot hunt&target.
     * 
     * @param ocean Riferimento all'oceano nemico.
     * @param fleet Riferimento alla flotta nemica.
     */
    HuntAndTarget(Ocean& ocean, Fleet& fleet);

    /**
     * @brief esegue la strategia del bot (caccia e bersaglia).
     */
    void doMove() override;
    
protected:
    /**
     * @brief Esegue la fase di caccia della strategia (colpisce casualmente).
     */
    virtual void hunt();

    /**
     * @brief Aggiunge le celle adiacenti alla cella contenente una nave trovata.
     * 
     * @param x cordinata x della cella trovata.
     * @param y cordinata y della cella trovata.
     */
    void addCloseCells(int x, int y);

    /**
     * @brief Aggiunge la cella con le coordinate x,y alla lista dei bersagli.
     * 
     * @param x cordinata x della cella.
     * @param y cordinata y della cella.
     */
    virtual void addToTargets(int x, int y);

    /**
     * @brief Esegue la fase di mira della strategia (colpisce celle presenti nella lista dei bersagli).
     */
    virtual void target();

    std::deque<std::reference_wrapper<Cell>> target_list_;  ///< lista dei bersagli.
};

#endif