#include "random.h"

Random::Random(Ocean& ocean) : BotAlgorithm(ocean){  
}
void Random::doMove(){
    while(true){
        try{
            ocean_.getCell(rand()%columns_, rand()%rows_).setIsHit();
            break;
        }catch(const std::exception& e){};
    }
}