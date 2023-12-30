#include "parity.h"

Parity::Parity(Ocean& ocean) : HuntAndTarget(ocean){
}

void Parity::hunt(){
    while(true){
        int x = rand()%columns_;
        int y = rand()%rows_;
        if((x & 1) != (y & 1)){     //se x e y hanno parita diversa (uno pari e uno dispari) incrementa di 1 y in modo da modificarne la parita
            y = (++y)%rows_;
        }
        try{
            hitAndCheck(x, y);
            break;
        }catch(const std::exception& e){};
    }
}