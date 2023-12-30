#include "random.h"

Random::Random(Ocean& ocean) : ocean_(ocean){  
    columns_ = ocean_.getNumberOfColumns();
    rows_ = ocean_.getNumberOfRows();
}
void Random::doMove(){
    while(true){
        try{
            ocean_.getCell(rand()%columns_, rand()%rows_).setIsHit();
            break;
        }catch(const std::exception& e){};
    }
}