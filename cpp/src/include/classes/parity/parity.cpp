#include "parity.h"

Parity::Parity(Ocean& ocean, Fleet& fleet) : HuntAndTarget(ocean, fleet){}

void Parity::hunt(){
    while(true){
        int x = rand() % columns_;
        int y = rand() % rows_;

        if((x & 1) != (y & 1)){     //se x e y hanno parita diversa (lsb diverso) incrementa di 1 y in modo da modificarne la parita
            y = (++y) % rows_;
        }
        if(hitAndNotify(x,y)){
            addCloseCells(x, y);
            break;
        }
    }
}