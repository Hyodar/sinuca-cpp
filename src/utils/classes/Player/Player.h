
#ifndef PLAYER_H_
#define PLAYER_H_

#include "../Ball/Ball.h"

class Player
{
    public:
        void setGameConfig();
        
        void addBall();

        void addBall(int posX, int posY, int vX, int vY);

        void throwBall();

        void randomBalls(int n);

        void drawLine();
    
    private:
        void addToVector(Ball& b);
};

#endif