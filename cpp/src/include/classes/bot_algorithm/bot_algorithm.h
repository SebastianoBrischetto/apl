#include "../ocean/ocean.h"

class BotAlgorithm{
    public:
        BotAlgorithm(Ocean& ocean);
        virtual void doMove() = 0;

    private:
        int columns_;
        int rows_;
        Ocean& ocean_;
};