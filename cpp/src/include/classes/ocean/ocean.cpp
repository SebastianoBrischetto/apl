#include "ocean.h"

Ocean::Ocean(int columns, int rows) :
    columns_(columns),
    rows_(rows)
{
    int dimension = columns_ * rows_;
    // Reserves the necessary memory space to avoid the overhead of shifting elements during insertion
    ocean_.reserve(dimension);
    for (int i = 0; i < dimension; ++i) {
        // Emplace_back initializes and loads the object into the vector (no temporary object is created)
        ocean_.emplace_back(i % columns_, i / columns_);
    }
}

int Ocean::getNumberOfRows() const { return rows_; }

int Ocean::getNumberOfColumns() const { return columns_; }

bool Ocean::areCordsSafe(int x, int y) const { return (x >= 0 && x < columns_ && y >= 0 && y < rows_); }

Cell& Ocean::getCell(int x, int y) {
    if (!areCordsSafe(x, y)) {
        throw std::runtime_error("Out of bounds");
    }
    return ocean_[x + y * columns_];
}

Cell& Ocean::getMaxProbabilityCell() {
    int max_probability = 0;
    int index_of_max_probability = 0;

    for (int i = 0; i < ocean_.size(); ++i) {
        int current_cell_probability = ocean_[i].getOccupiedProbability();
        if (max_probability < current_cell_probability || (max_probability == current_cell_probability && rand() % 2 == 1)) {
            max_probability = current_cell_probability;
            index_of_max_probability = i;
        }
    }
    return ocean_[index_of_max_probability];
}

bool Ocean::isSpaceOccupied(int init_x_cord, int init_y_cord, Direction direction, int length) {
    int x = init_x_cord;
    int y = init_y_cord;

    for (int i = 0; i < length; ++i) {
        if (getCell(x, y).getIsOccupied()) {
            return true;
        }
        updateCoords(x, y, x, y, 1, direction);
    }
    return false;
}

int Ocean::getMaxUnhitSpace(int init_x_cord, int init_y_cord, Direction direction, int length, bool target) {
    int unhit_cells = 0;
    int x = init_x_cord;
    int y = init_y_cord;

    for (int i = 0; i < length; ++i) {
        if (!areCordsSafe(x, y) || (!target && getCell(x, y).getIsHit()) || (target && getCell(x, y).getIsHit() && !getCell(x, y).getIsOccupied())) {
            break;
        }
        unhit_cells = i;
        updateCoords(x, y, x, y, 1, direction);
    }
    return unhit_cells;
}

void Ocean::updateCoords(int x_init_value, int y_init_value, int& x_reference, int& y_reference, int increment, Direction direction) {
    switch (direction) {
        case UP:
            x_reference = x_init_value;
            y_reference = y_init_value - increment;
            break;
        case RIGHT:
            x_reference = x_init_value + increment;
            y_reference = y_init_value;
            break;
        case DOWN:
            x_reference = x_init_value;
            y_reference = y_init_value + increment;
            break;
        case LEFT:
            x_reference = x_init_value - increment;
            y_reference = y_init_value;
            break;
    }
}

void Ocean::calcOceanProbability(int destroyers, int submariness_and_cruisers, int battleships, int carriers) {
    cleanOceanProbability();
    for (Cell& cell : ocean_) {
        int x = cell.getXCord();
        int y = cell.getYCord();
        calcDirectionProbability(x, y, RIGHT, destroyers, submariness_and_cruisers, battleships, carriers);
        calcDirectionProbability(x, y, DOWN, destroyers, submariness_and_cruisers, battleships, carriers);
    }
}

void Ocean::cleanOceanProbability() {
    for (Cell& cell : ocean_) {
        cell.resetOccupiedProbability();
    }
}

void Ocean::calcDirectionProbability(
    int init_x_cord, int init_y_cord, Direction direction,
    int destroyers, int submariness_and_cruisers, int battleships, int carriers,
    bool target, int bonus)
{
    int x = init_x_cord;
    int y = init_y_cord;
    int probability = 0;
    // Retrieve how much space is free in the specified direction (5 given by the max ship size)
    int unhit_cells = getMaxUnhitSpace(init_x_cord, init_y_cord, direction, 5, target);

    // For all free space, increment the probability in reverse order
    for (int i = unhit_cells; i >= 0; --i) {
        updateCoords(init_x_cord, init_y_cord, x, y, i, direction);
        bool isCellHit = getCell(x, y).getIsHit();
        bool isCellOccupied = getCell(x, y).getIsOccupied();
        updateProbability(probability, i, destroyers, submariness_and_cruisers, battleships, carriers, target);
        // In target mode (target = true), do not increment the probability of the original cell and cells hit and sunk.
        if (target && ((x == init_x_cord && y == init_y_cord) || (isCellHit && isCellOccupied))) {
            continue;
        }
        getCell(x, y).increaseOccupiedProbability(probability + bonus);
    }
}

void Ocean::calcTargetProbability(int target_x, int target_y,
    int destroyers, int submarines_and_cruisers, int battleships, int carriers,
    int vertical_bonus, int horizontal_bonus)
{
    int bonus = 0;
    cleanOceanProbability();
    for (Direction direction : {UP, RIGHT, DOWN, LEFT}) {
        bonus = (direction == UP || direction == DOWN) ? horizontal_bonus : vertical_bonus;
        calcDirectionProbability(target_x, target_y, direction, destroyers, submarines_and_cruisers, battleships, carriers, true, bonus);
    }
}

void Ocean::updateProbability(int& probability, int index, int destroyers, int submariness_and_cruisers, int battleships, int carriers, bool target) {
    switch (index) {
        case 4: probability += carriers; break;
        case 3: probability += battleships; break;
        case 2: probability += submariness_and_cruisers; break;
        case 1: probability += destroyers + (target) ? 1 : 0; break; // Increment probability at distance 1 to prioritize adjacent cells in target mode
    }
}
