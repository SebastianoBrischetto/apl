#include "random.h"

Random::Random(Ocean& ocean, Fleet& fleet) : BotAlgorithm(ocean, fleet){}

void Random::doMove(){
    if(counter_ >= columns_ * rows_){
        return;
    }
    hitRandomly();
    counter_++;
}

void Random::hitRandomly(){
    while(true){
        if(hitAndNotify(rand()%columns_, rand()%rows_)){
            break;
        }
    }
}