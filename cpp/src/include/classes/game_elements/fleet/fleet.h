#ifndef FLEET_H_
#define FLEET_H_

#include <list>
#include "../ships/include_ships.h"

// Tipi di nave
enum ShipType{
    DESTROYER = 2,  ///< Nave di lunghezza 2.
    SUBMARINE = 3,  ///< Nave di lunghezza 3.
    CRUISER = 1,    ///< Nave di lunghezza 3.
    BATTLESHIP = 4, ///< Nave di lunghezza 4.
    CARRIER = 5     ///< Nave di lunghezza 5.
};

/**
 * @class Fleet
 * @brief Rappresenta un gruppo di navi.
 */
class Fleet{

public:
    /**
     * @brief Costruttore della flotta del giocatore.
     * 
     * @param ocean Riferimento all'oceano della flotta.
     */
    Fleet(Ocean& ocean);

    /**
     * @brief Aggiunge navi già create alla flotta.
     * 
     * @param ship Nave da aggiungere.
     * 
     * @throw std::runtime_error Se si prova ad aggiungere navi appartenenti ad oceani diversi da quello della flotta.
     */
    void addToFleet(Ship& ship);

    /**
     * @brief Aggiunge navi di un determinato tipo alla flotta piazzate in modo casuale.
     * 
     * @param ship_type Tipo delle navi che devono essere create.
     * @param number_of_ships Numero di navi da creare.
     * @param ocean Riferimento all'oceano nella quale le navi verranno piazzate.
     * 
     * @throw std::runtime_error Se si prova ad aggiungere navi appartenenti ad oceani diversi da quello della flotta.
     */
    void addToFleet(ShipType ship_type, int number_of_ships, Ocean& ocean);

    /**
     * @brief Ritorna il numero totale di navi della flotta.
     * 
     * @return Numero di navi a galla.
     */
    int getNumberOfShips();

   /**
     * @brief Ritorna il numero di destroyers della flotta.
     * 
     * @return Numero di destroyers della flotta.
     */
    int getNumberOfDestroyers();

    /**
     * @brief Ritorna il numero di submarines e cruisers della flotta.
     * 
     * @return Numero di submarines e cruisers della flotta.
     */
    int getNumberOfSubmarinesAndCruisers();

    /**
     * @brief Ritorna il numero di battleships della flotta.
     * 
     * @return Numero di battleships della flotta.
     */
    int getNumberOfBattleships();

    /**
     * @brief Ritorna il numero di carriers della flotta.
     * 
     * @return Numero di carriers della flotta.
     */
    int getNumberOfCarriers();

    /**
     * @brief Ritorna una nave della flotta.
     * 
     * @param i indice della nave
     * 
     * @return Riferimento alla nave.
     * 
     * @throw std::runtime_error Se si prova ad accedere ad un elemento out of bounds.
     */
    Ship& getShip(int i);

    /**
     * @brief Ritorna il riferimento all'oceano della flotta.
     * 
     * @return Riferimento oceano.
     */
    Ocean& getFleetOcean();

    /**
     * @brief Ritorna la copia dell'ultima nave distrutta.
     * 
     * @return Riferimento all'ultima nave distrutta.
     */
    Ship& getLastSunkShip();

    /**
     * @brief Controlla se la flotta è stata completamente distrutta.
     * 
     * @return True se la flotta è stata distrutta, false in caso contrario.
     */
    bool getIsFleetDestroyed();

    /**
     * @brief Aggiorna il numero di navi della flotta in base al tipo della nave.
     * 
     * @param ship Riferimento alla nave che sta venendo aggiunta.
     * @param value Valore da aggiungere o sottrarre al numero di navi.
     */
    void updateFleetNumbers(Ship& ship, int value);

    /**
     * @brief Aggiorna il numero di navi presenti nella flotta quando viene colpita una nave.
     */
    void updateFleetNumbersOnHit();

    /**
     * @brief Crea una nave del tipo richiesto con piazzamento fornito.
     * 
     * @param ship_type Tipo delle nave che deve essere creata.
     * @param x Coordinata x da cui iniziare a piazzare la nave.
     * @param y Coordinata y da cui iniziare a piazzare la nave.
     * @param direction Direzione verso la quale piazzare la nave.
     * @param ocean Riferimento all'oceano nella quale la nave verrà piazzata.
     * 
     * @return Il riferimento alla nave creata.
     * 
     * @throw std::runtime_error Se si prova a creare una nave non supportata.
     */
    static Ship createTypeOfShip(ShipType ship_type, int x, int y, Direction direction, Ocean& ocean);
private:
    
    int destroyers_, submarines_and_cruisers_, battleships_, carriers_; ///< Numero dei vari tipi di nave.
    std::list<Ship> fleet_;                                             ///< Lista di navi che compongono la flotta.
    Ocean& ocean_;                                                       ///< Riferimento all'ocean della flotta
    Ship last_sunk_ship_;                                               ///< Copia dell'ultima nave affondata
};

#endif