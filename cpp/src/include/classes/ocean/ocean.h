#include <vector>
#include "../cell/cell.h"

enum Direction{
    UP,     //0
    RIGHT,  //1
    DOWN,   //2
    LEFT    //3
};

class Ocean{
    public:
        Ocean(int rows_, int columns_);

        bool isSpaceOccupied(int init_x_cord, int init_y_cord, Direction direction, int length);

        int getNumberOfRows();
        int getNumberOfColumns();
        Cell& getCell(int x, int y);
        
    private:
        int rows_;
        int columns_;
        std::vector<Cell> ocean_;
};