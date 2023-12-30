#include "../bot_algorithm/bot_algorithm.h"

class Random : public BotAlgorithm{

    public:
        Random(Ocean& ocean);
        void doMove() override;
};