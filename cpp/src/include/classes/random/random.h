#ifndef RANDOM_H_
#define RANDOM_H_
#include "../bot_algorithm/bot_algorithm.h"

class Random : public BotAlgorithm{

    public:
        Random(Ocean& ocean);
        void doMove() override;
};

#endif