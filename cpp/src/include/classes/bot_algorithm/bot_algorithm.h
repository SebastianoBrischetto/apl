#ifndef BOT_ALGORITHM_H_
#define BOT_ALGORITHM_H_
#include "../fleet/fleet.h"

class BotAlgorithm{
    public:
        BotAlgorithm(Ocean& ocean, Fleet& fleet);
        virtual void doMove() = 0;
        bool hitAndNotify(int x, int y);

    protected:
        int columns_;
        int rows_;
        Ocean& ocean_;
        Fleet& fleet_;
};

#endif