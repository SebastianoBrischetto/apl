#ifndef BOT_ALGORITHM_H_
#define BOT_ALGORITHM_H_
#include "../ocean/ocean.h"

class BotAlgorithm{
    public:
        BotAlgorithm(Ocean& ocean);
        virtual void doMove() = 0;

    protected:
        int columns_;
        int rows_;
        Ocean& ocean_;
};

#endif