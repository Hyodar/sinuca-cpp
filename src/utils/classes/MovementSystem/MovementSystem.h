
#ifndef MOV_H_
#define MOV_H_

#include "../Ball/Ball.h"

class MovementSystem
{
    public:
        void process();

    private:
        void moveBall(Ball& ball);
};

#endif