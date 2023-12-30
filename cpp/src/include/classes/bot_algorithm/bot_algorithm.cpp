#include "bot_algorithm.h"
BotAlgorithm::BotAlgorithm(Ocean& ocean) : ocean_(ocean){
    rows_ = ocean_.getNumberOfRows();
    columns_ = ocean_.getNumberOfColumns();
}