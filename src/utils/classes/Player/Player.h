
#ifndef PLAYER_H_
#define PLAYER_H_

#include "../Ball/Ball.h"

class Player
{
    public:
        void addBall();

        void addBall(int posX, int posY, int vX, int vY);

        void throwBall(int mouseClickX, int mouseClickY, int mouseUpX, int mouseUpY);

        void randomBalls(int n);

        void setGameConfig();
    
    private:
        void addToVector(Ball& b);
};

#endif