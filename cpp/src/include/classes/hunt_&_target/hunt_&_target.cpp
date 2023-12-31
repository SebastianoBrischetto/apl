#include "hunt_&_target.h"

HuntAndTarget::HuntAndTarget(Ocean& ocean, Fleet& fleet) : BotAlgorithm(ocean, fleet){}
void HuntAndTarget::doMove(){
    if(target_list_.size() == 0){
        hunt();
    }else{
        target();
    }
}

void HuntAndTarget::hunt(){
    while(true){
        int x = rand()%columns_;
        int y = rand()%rows_;
        if(hitAndNotify(x,y)){
            addCloseCells(x, y);
            break;
        }
    }
}

void HuntAndTarget::addCloseCells(int x, int y){
    if(ocean_.getCell(x,y).getIsOccupied()){
        addToTargets(x, y-1);    //UP
        addToTargets(x+1, y);    //RIGHT
        addToTargets(x, y+1);    //DOWN
        addToTargets(x-1, y);    //LEFT
    }
}

void HuntAndTarget::addToTargets(int x, int y){
    if((x < 0 || x >= columns_) || (y < 0 || y >= rows_) || ocean_.getCell(x, y).getIsHit()){
        return;
    }
    target_list_.push_back(ocean_.getCell(x, y));
}

void HuntAndTarget::target(){
    if(!target_list_.front().get().getIsHit()){
        int x = target_list_.front().get().getXCord();
        int y = target_list_.front().get().getYCord();
        if(hitAndNotify(x,y)){
            addCloseCells(x, y);
        }
        
    }
    target_list_.pop_front();
}