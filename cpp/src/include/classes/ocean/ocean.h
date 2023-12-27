#include <vector>
#include "../cell/cell.h"

class Ocean{
    public:
        Ocean(int rows_, int columns_);

        Cell& getCell(int x, int y);
        
    private:
        int rows_;
        int columns_;
        int dimension_;
        std::vector<Cell> ocean_;
};