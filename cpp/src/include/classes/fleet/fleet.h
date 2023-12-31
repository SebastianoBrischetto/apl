#ifndef FLEET_H_
#define FLEET_H_
#include <list>
#include "../include_ships.h"

enum ShipType{
    DESTROYER,
    SUBMARINE,
    CRUISER,
    BATTLESHIP,
    CARRIER
};

class Fleet{
    public:
        /**
         * Costruttore della flotta del player con nave gia esistente.
         * 
         * Inizializza un oggetto flotta composto da oggetti nave
         * 
         * @param ship riferimento a una nave gia esistente
         */
        Fleet(Ship& ship);

        /**
         * Costruttore della flotta del player con navi di un determinato tipo piazzate in modo casuale.
         * 
         * Inizializza un oggetto flotta composto da oggetti nave
         * 
         * @param ship_type tipo delle navi che devono essere create
         * @param number_of_ships numero di navi da creare
         * @param ocean riferimento all'oceano nella quale le navi veranno piazzate
         */
        Fleet(ShipType ship_type, int number_of_ships, Ocean& ocean);

        /**
         * Aggiunge navi gia create alla flotta
         * 
         * @param ship nave da aggiungere
         */
        void addToFleet(Ship& ship);

        /**
         * Aggiunge navi di un determinate tipo alla flotta piazzate in modo casuale
         * 
         * @param ship_type tipo delle navi che devono essere create
         * @param number_of_ships numero di navi da creare
         * @param ocean riferimento all'oceano nella quale le navi veranno piazzate
         */
        void addToFleet(ShipType ship_type, int number_of_ships, Ocean& ocean);

        void updateFleetStatus();
        //Torna un bool che indica se la flotta e stata distrutta (true) o meno
        bool getIsFleetDestroyed();

        int getNumberOfShips();
        
    private:
        bool is_fleet_destroyed_;
        std::list<Ship> fleet_;

        /**
         * Crea una nave del tipo richiesto con piazzamento casuale
         * 
         * @param ship_type tipo delle nave che deve essere creata
         * @param ocean riferimento all'oceano nella quale la nave verra piazzata
         * 
         * @throw se si prova a creare una nave non supportata
         */
        Ship createTypeOfShip(ShipType ship_type, Ocean& ocean);
};

#endif