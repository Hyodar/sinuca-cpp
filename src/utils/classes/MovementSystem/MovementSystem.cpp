
#include <SDL.h>

#include <cmath>
#include <vector>

#include "../../../include/constants.h"
#include "../Ball/Ball.h"

#include "MovementSystem.h"

extern int gMinPoint[];
extern int gScreenSize[];
extern std::vector<Ball> gBalls;

// ----------------------------------------------------------------------------

void MovementSystem::process() {
    for(Ball& ball: gBalls) this->moveBall(ball);
}

// ----------------------------------------------------------------------------

void MovementSystem::moveBall(Ball& ball) {
    ball.posX += round(ball.vX);
    ball.posY += round(ball.vY);

    ball.posX = std::max(ball.posX, gMinPoint[0]);
    ball.posY = std::max(ball.posY, gMinPoint[1]);

    // TODO: rever isso ############################
    if(ball.posX + BALL_DIAMETER > gScreenSize[0]) {
        ball.posX = gScreenSize[0] - BALL_DIAMETER;
    }
    if(ball.posY + BALL_DIAMETER > gScreenSize[1]) {
        ball.posY = gScreenSize[1] - BALL_DIAMETER;
    }
}