
#include <SDL.h>

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "../../../include/constants.h"

#include "../Ball/Ball.h"

#include "Player.h"

extern SDL_Renderer* gRenderer;
extern std::vector<Ball> gBalls;
extern int gScreenSize[];
extern int gMinPoint[];

extern int gMouseClickX;
extern int gMouseClickY;

extern int gMouseMotionX;
extern int gMouseMotionY;

// -----------------------------------------------------------------------

void Player::addBall(int posX, int posY, int vX, int vY) {
    Ball ball(posX, posY, vX, vY);
    addToVector(ball);
}

// -----------------------------------------------------------------------

void Player::throwBall() {
    Ball ball  (gMouseClickX - BALL_RADIUS,
                gMouseClickY - BALL_RADIUS,
                (gMouseClickX - gMouseMotionX)/PINCH_FACTOR,
                (gMouseClickY - gMouseMotionY)/PINCH_FACTOR);
    addToVector(ball);
}

// -----------------------------------------------------------------------

void Player::randomBalls(int nBalls) {
    srand(time(NULL));

    for(int i=0; i<nBalls; i++) {
        Ball ball  ((rand() % (gScreenSize[0] - gMinPoint[0])) + gMinPoint[0],
                    (rand() % (gScreenSize[1] - gMinPoint[1])) + gMinPoint[1],
                    (rand() % 4*DEFAULT_RAND_VEL_RNG) - 2*DEFAULT_RAND_VEL_RNG,
                    (rand() % 4*DEFAULT_RAND_VEL_RNG) - 2*DEFAULT_RAND_VEL_RNG);
        addToVector(ball);
    }
}

// -----------------------------------------------------------------------

void Player::addBall() {
    Ball ball;
    addToVector(ball);
}

// -----------------------------------------------------------------------

void Player::addToVector(Ball& ball) {
    gBalls.push_back(ball);
}

// -----------------------------------------------------------------------

void Player::drawLine() {
    SDL_SetRenderDrawColor(gRenderer,
                            DEFAULT_LINE_COLOR[0],
                            DEFAULT_LINE_COLOR[1],
                            DEFAULT_LINE_COLOR[2],
                            DEFAULT_LINE_COLOR[3]);
    SDL_RenderDrawLine(gRenderer, gMouseClickX, gMouseClickY, gMouseMotionX, gMouseMotionY); // FIXME!
}

// -----------------------------------------------------------------------