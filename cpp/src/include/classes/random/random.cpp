#include "random.h"

Random::Random(Ocean& ocean, Fleet& fleet) : BotAlgorithm(ocean, fleet){  
}
void Random::doMove(){
    while(true){
        if(hitAndNotify(rand()%columns_, rand()%rows_)){
            break;
        }
    }
}