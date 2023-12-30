#include "../bot_algorithm/bot_algorithm.h"

class Random : public BotAlgorithm{

    public:
        Random(Ocean& ocean);
        void doMove();
        
    private:
        Ocean& ocean_;
        int columns_;
        int rows_;
};