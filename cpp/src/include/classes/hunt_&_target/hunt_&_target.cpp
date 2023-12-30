#include "hunt_&_target.h"

HuntAndTarget::HuntAndTarget(Ocean& ocean) : BotAlgorithm(ocean){}
void HuntAndTarget::doMove(){
    if(search_list_.size() == 0){
        hunt();
    }else{
        search();
    }
}

void HuntAndTarget::hunt(){
    while(true){
        int x = rand()%columns_;
        int y = rand()%rows_;
        try{
            hitAndCheck(x, y);
            break;
        }catch(const std::exception& e){};
    }
}

void HuntAndTarget::hitAndCheck(int x, int y){
    ocean_.getCell(x, y).setIsHit();
    if(ocean_.getCell(x,y).getIsOccupied()){
        addToSearch(x, y-1);    //UP
        addToSearch(x+1, y);    //RIGHT
        addToSearch(x, y+1);    //DOWN
        addToSearch(x-1, y);    //LEFT
    }
}

void HuntAndTarget::addToSearch(int x, int y){
    if((x < 0 || x >= columns_) || (y < 0 || y >= rows_) || ocean_.getCell(x, y).getIsHit()){
        return;
    }
    search_list_.push_back(ocean_.getCell(x, y));
}

void HuntAndTarget::search(){
    if(!search_list_.front().get().getIsHit()){
        int x = search_list_.front().get().getXCord();
        int y = search_list_.front().get().getYCord();
        hitAndCheck(x, y);
    }
    search_list_.pop_front();
}