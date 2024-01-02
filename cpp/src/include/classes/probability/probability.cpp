#include "probability.h"

Probability::Probability(Ocean& ocean, Fleet& fleet) : HuntAndTarget(ocean, fleet){
    number_of_ships_ = fleet_.getNumberOfShips();
}

void Probability::hunt(){
    ocean_.calcOceanProbability(fleet_.getNumberOfDestroyers(), fleet_.getNumberOfSubmarinesAndCruisers(), fleet_.getNumberOfBattleships(), fleet_.getNumberOfCarriers());
    Cell& cell = ocean_.getMaxProbabilityCell();
    int x = cell.getXCord();
    int y = cell.getYCord();
    if(hitAndNotify(x,y) && cell.getIsOccupied()){
        addToTargets(x, y);
    }
}

void Probability::addToTargets(int x, int y){
    target_list_.emplace_back(ocean_.getCell(x, y));
}

void Probability::target(){
    Cell& current_target = target_list_.back().get();
    int current_x = current_target.getXCord();
    int current_y = current_target.getYCord();
    int horizontal_bonus = 0;
    int vertical_bonus = 0;
    
    if(target_list_.size() >= 2){
        vertical_bonus = isPrevTargetHorizontal()? number_of_ships_ : 0;
        horizontal_bonus = !isPrevTargetHorizontal()? number_of_ships_ : 0;
    }
    ocean_.calcTargetProbability(   current_x, current_y, 
                                    fleet_.getNumberOfDestroyers(), fleet_.getNumberOfSubmarinesAndCruisers(), fleet_.getNumberOfBattleships(), fleet_.getNumberOfCarriers(),
                                    vertical_bonus, horizontal_bonus);

    int target_x, target_y;
    target_x = ocean_.getMaxProbabilityCell().getXCord();
    target_y = ocean_.getMaxProbabilityCell().getYCord();
    if(hitAndNotify(target_x, target_y) && ocean_.getCell(target_x, target_y).getIsOccupied()){
        addToTargets(target_x, target_y);
    }
    emptyTargetList();
}

void Probability::emptyTargetList(){
    if(number_of_ships_ != fleet_.getNumberOfShips()){
        number_of_ships_ = fleet_.getNumberOfShips();
        Ship& last_sunk_ship = fleet_.getLastSunkShip();
        int num_of_pieces = last_sunk_ship.getLength();
        for( int i = target_list_.size() - 1; i >= 0; --i){
            int x = target_list_[i].get().getXCord();
            int y = target_list_[i].get().getYCord();
            for(int j = 0 ; j < num_of_pieces; ++j){
                if(x == last_sunk_ship.getPiece(j).getXCord() && y == last_sunk_ship.getPiece(j).getYCord()){
                    std::deque<std::reference_wrapper<Cell>>::iterator it = target_list_.begin() + i;
                    target_list_.erase(it);
                }
            }
        }
    }
}

bool Probability::isPrevTargetHorizontal(){
    if(target_list_[target_list_.size() - 2].get().getXCord() != target_list_.back().get().getXCord()){
        return true;
    }
    return false;
}