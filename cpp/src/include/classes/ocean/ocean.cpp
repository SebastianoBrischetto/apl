#include "ocean.h"

Ocean::Ocean(int columns, int rows) :
    columns_(columns),
    rows_(rows)
{
    int dimension = columns_ * rows_;
    // Riserva lo spazion necessario in modo da evitare l'overhead dovuto allo shift durante l'inserimento
    ocean_.reserve(dimension);
    for (int i = 0; i < dimension; ++i) {
        ocean_.emplace_back(i % columns_, i / columns_);
    }
}

int Ocean::getNumberOfRows() const {
    return rows_;
}

int Ocean::getNumberOfColumns() const {
    return columns_;
}

bool Ocean::areCoordinatesValid(int x, int y) const {
    return (x >= 0 && x < columns_ && y >= 0 && y < rows_);
}

Cell& Ocean::getCell(int x, int y) {
    if (!areCoordinatesValid(x, y)) {
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

bool Ocean::isSpaceOccupied(int init_x, int init_y, Direction direction, int length) {
    int x = init_x;
    int y = init_y;

    for (int i = 0; i < length; ++i) {
        if (getCell(x, y).getIsOccupied()) {
            return true;
        }
        updateCoordinates(x, y, x, y, 1, direction);
    }
    return false;
}

int Ocean::getMaxUnhitSpace(int init_x, int init_y, Direction direction, int length, bool target) {
    int x = init_x;
    int y = init_y;
    int unhit_cells = 0;
    for (int i = 0; i < length; ++i) {
        if (!areCoordinatesValid(x, y) || (!target && getCell(x, y).getIsHit()) || (target && getCell(x, y).getIsHit() && !getCell(x, y).getIsOccupied())) {
            break;
        }
        unhit_cells = i;
        updateCoordinates(x, y, x, y, 1, direction);
    }
    return unhit_cells;
}

void Ocean::updateCoordinates(int x_init_value, int y_init_value, int& x_reference, int& y_reference, int increment, Direction direction) {
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

void Ocean::calcOceanProbability(int destroyers, int submarines_and_cruisers, int battleships, int carriers) {
    resetOceanProbability();
    for (Cell& cell : ocean_) {
        int x = cell.getXCoord();
        int y = cell.getYCoord();
        calcDirectionProbability(x, y, RIGHT, destroyers, submarines_and_cruisers, battleships, carriers);
        calcDirectionProbability(x, y, DOWN, destroyers, submarines_and_cruisers, battleships, carriers);
    }
}

void Ocean::resetOceanProbability() {
    for (Cell& cell : ocean_) {
        cell.resetOccupiedProbability();
    }
}

void Ocean::calcDirectionProbability(   int init_x, int init_y, Direction direction, 
                                        int destroyers, int submarines_and_cruisers, int battleships, int carriers, 
                                        bool target, int bonus)
{
    int x = init_x;
    int y = init_y;
    int probability = 0;
    int unhit_cells = getMaxUnhitSpace(init_x, init_y, direction, 5, target);

    for (int i = unhit_cells; i >= 0; --i) {
        updateCoordinates(init_x, init_y, x, y, i, direction);
        bool isCellHit = getCell(x, y).getIsHit();
        bool isCellOccupied = getCell(x, y).getIsOccupied();
        updateProbability(probability, i, destroyers, submarines_and_cruisers, battleships, carriers, target);
        // In modalita target (target = true), non viene aumentata la probabilita della cella di origine e delle celle colpite e affondate.
        if (target && ((x == init_x && y == init_y) || (isCellHit && isCellOccupied))) {
            continue;
        }
        getCell(x, y).increaseOccupiedProbability(probability + bonus);
    }
}

void Ocean::calcTargetProbability(  int target_x, int target_y, 
                                    int destroyers, int submarines_and_cruisers, int battleships, int carriers, 
                                    int vertical_bonus, int horizontal_bonus)
{
    int bonus = 0;
    resetOceanProbability();
    for (Direction direction : {UP, RIGHT, DOWN, LEFT}) {
        bonus = (direction == UP || direction == DOWN) ? horizontal_bonus : vertical_bonus;
        calcDirectionProbability(target_x, target_y, direction, destroyers, submarines_and_cruisers, battleships, carriers, true, bonus);
    }
}

void Ocean::updateProbability(int& probability, int index, int destroyers, int submarinesAndCruisers, int battleships, int carriers, bool target) {
    switch (index) {
        case 4: probability += carriers; break;
        case 3: probability += battleships; break;
        case 2: probability += submarinesAndCruisers; break;
        case 1: probability += destroyers + (target ? 1 : 0); break; // Viene aumentata la probabilita delle celle immediatamente adiacenti in modalita target
    }
}
