#include "probability.h"

Probability::Probability(Ocean& ocean, Fleet& fleet) : 
    HuntAndTarget(ocean, fleet) 
{
    number_of_ships_ = fleet_.getNumberOfShips();
}

void Probability::hunt() {
    ocean_.calcOceanProbability(fleet_.getNumberOfDestroyers(), fleet_.getNumberOfSubmarinesAndCruisers(), fleet_.getNumberOfBattleships(), fleet_.getNumberOfCarriers());
    Cell& cell = ocean_.getMaxProbabilityCell();
    int x = cell.getXCoord();
    int y = cell.getYCoord();
    if (hitAndNotify(x, y) && cell.getIsOccupied()) {
        addToTargets(x, y);
    }
}

void Probability::addToTargets(int x, int y) {
    target_list_.emplace_back(ocean_.getCell(x, y));
}

bool Probability::target() {
    Cell& current_target = target_list_.back().get();
    int current_x = current_target.getXCoord();
    int current_y = current_target.getYCoord();
    int horizontal_bonus = 0;
    int vertical_bonus = 0;

    if (target_list_.size() >= 2) {
        vertical_bonus = isPrevTargetHorizontal() ? number_of_ships_ : 0;
        horizontal_bonus = !isPrevTargetHorizontal() ? number_of_ships_ : 0;
    }
    ocean_.calcTargetProbability(current_x, current_y,
                                  fleet_.getNumberOfDestroyers(), fleet_.getNumberOfSubmarinesAndCruisers(), fleet_.getNumberOfBattleships(), fleet_.getNumberOfCarriers(),
                                  vertical_bonus, horizontal_bonus);
    Cell& max_probability_cell = ocean_.getMaxProbabilityCell();

    if (max_probability_cell.getOccupiedProbability() <= 0) {
        return false;
    }
    int target_x = max_probability_cell.getXCoord();
    int target_y = max_probability_cell.getYCoord();

    if (hitAndNotify(target_x, target_y) && max_probability_cell.getIsOccupied()) {
        addToTargets(target_x, target_y);
    }
    emptyTargetList();
    return true;
}

void Probability::emptyTargetList() {
    if (number_of_ships_ != fleet_.getNumberOfShips()) {
        number_of_ships_ = fleet_.getNumberOfShips();
        Ship& last_sunk_ship = fleet_.getLastSunkShip();
        int num_of_pieces = last_sunk_ship.getLength();
        for (int i = target_list_.size() - 1; i >= 0; --i) {
            int x = target_list_[i].get().getXCoord();
            int y = target_list_[i].get().getYCoord();
            for (int j = 0; j < num_of_pieces; ++j) {
                if (x == last_sunk_ship.getShipPiece(j).getXCoord() && y == last_sunk_ship.getShipPiece(j).getYCoord()) {
                    auto it = target_list_.begin() + i;
                    target_list_.erase(it);
                }
            }
        }
    }
}

bool Probability::isPrevTargetHorizontal() {
    if (target_list_[target_list_.size() - 2].get().getXCoord() != target_list_.back().get().getXCoord()) {
        return true;
    }
    return false;
}