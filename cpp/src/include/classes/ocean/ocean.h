#include <vector>
#include <stdexcept>
#include "../cell/cell.h"

class Ocean{
    public:
        Ocean(int rows_, int columns_);
        bool isSpaceOccupied(int init_x_cord, int init_y_cord, int direction, int length);
        int getNumberOfRows();
        int getNumberOfColumns();
        Cell& getCell(int x, int y);
        
    private:
        int rows_;
        int columns_;
        int dimension_;
        std::vector<Cell> ocean_;
};