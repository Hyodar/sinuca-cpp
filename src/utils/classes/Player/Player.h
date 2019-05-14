
#ifndef PLAYER_H_
#define PLAYER_H_

#include "../Ball/Ball.h"

class Player
{
    public:
        void addBall();

        void addBall(int posX, int posY, int vX, int vY);
    
    private:
        void addToVector(Ball& b);
};

#endif