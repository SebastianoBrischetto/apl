#include "random.h"

Random::Random(Ocean& ocean, Fleet& fleet) : BotAlgorithm(ocean, fleet) {}

void Random::doMove() {
    if (counter_ >= columns_ * rows_) {
        return;
    }
    hitRandomly();
    counter_++;
}

void Random::hitRandomly() {
    while (true) {
        int x = rand() % columns_;
        int y = rand() % rows_;
        
        if (hitAndNotify(x, y)) {
            break;
        }
    }
}