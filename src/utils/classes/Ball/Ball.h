
#ifndef BALL_H_
#define BALL_H_

class Ball
{
    public:

        // as posicoes sao tomadas como double, mas no render viram int
        double posX = 0;
        double posY = 0;
        double vX = 0;
        double vY = 0;
        
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

        int vSignX();

        int vSignY();

    private:
    
        double collisionAngle(Ball& ball2);

        void getDelta(Ball& ball2);

        double getCenterDistance(int dx, int dy);

        void unstuck(Ball& ball2, double sin, double cos);

        void ballCollision(Ball& ball2);

};

#endif // BALL_H_
