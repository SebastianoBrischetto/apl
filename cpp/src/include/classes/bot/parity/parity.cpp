#include "parity.h"

Parity::Parity(Ocean& ocean, Fleet& fleet) : 
    HuntAndTarget(ocean, fleet) 
{}

void Parity::hunt() {
    while (true) {
        int x = rand() % columns_;
        int y = rand() % rows_;

        // Se x e y hanno parità diversa (LSB diverso), incrementa y di 1 per modificarne la parità
        if ((x & 1) != (y & 1)) {
            y = (++y) % rows_;
        }

        if (hitAndNotify(x, y)) {
            addCloseCells(x, y);
            break;
        }
    }
}