#ifndef HUNT_AND_TARGET_H_
#define HUNT_AND_TARGET_H_
#include <deque>
#include <functional>
#include "../bot_algorithm/bot_algorithm.h"

class HuntAndTarget : public BotAlgorithm{
    public:
        HuntAndTarget(Ocean& ocean, Fleet& fleet);
        void doMove() override;
        
    protected:
        virtual void hunt();
        void addCloseCells(int x, int y);
        void addToTargets(int x, int y);
        void target();
        std::deque<std::reference_wrapper<Cell>> target_list_;
};

#endif