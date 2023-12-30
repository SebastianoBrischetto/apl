#ifndef HUNT_AND_TARGET_H_
#define HUNT_AND_TARGET_H_
#include <deque>
#include <functional>
#include "../bot_algorithm/bot_algorithm.h"

class HuntAndTarget : public BotAlgorithm{
    public:
        HuntAndTarget(Ocean& ocean);
        void doMove() override;
        
    protected:
        virtual void hunt();
        void hitAndCheck(int x, int y);
        void addToSearch(int x, int y);
        void search();
        std::deque<std::reference_wrapper<Cell>> search_list_;
};

#endif