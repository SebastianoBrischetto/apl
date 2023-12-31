#ifndef PARITY_H_
#define PARITY_H_
#include "../hunt_&_target/hunt_&_target.h"

class Parity: public HuntAndTarget{
    public:
        Parity(Ocean& ocean, Fleet& fleet);
        
    protected:
        void hunt() override;
};

#endif