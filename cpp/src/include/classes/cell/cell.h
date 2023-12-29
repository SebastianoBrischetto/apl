#ifndef CELL_H_
#define CELL_H_

class Cell {
public:
    Cell(int init_x_cord, int init_y_cord);

    int getXCord();

    int getYCord();

    void setIsHit();

    bool getIsHit();

    void setIsOccupied();

    bool getIsOccupied();

private:
    int x_cord_;
    int y_cord_;
    bool is_hit_;
    bool is_occupied_;
};

#endif