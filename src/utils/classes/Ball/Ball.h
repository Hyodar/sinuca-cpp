
#ifndef BALL_H_
#define BALL_H_

class Ball
{
    public:

        int posX = 0;
        int posY = 0;
        float vX = 0;
        float vY = 0;
        
        // distancia entre outra, para colisoes
        int dx = 0;
        int dy = 0;
        
        Ball(int posX, int posY, int vX, int vY);
        
        Ball(int vX, int vY);

        Ball();

        void render();

        void aim();

        void checkCollision(Ball& ball2);

        void wallCollision();

    private:
    
        float collisionAngle(Ball& ball2);

        void getDelta(Ball& ball2);

        float getCenterDistance(int dx, int dy);

        void unstuck(Ball& ball2, float sin, float cos);

        void ballCollision(Ball& ball2);

};

#endif // BALL_H_
