
#include <vector>

#include "../Ball/Ball.h"

#include "Player.h"

extern std::vector<Ball> gBalls;

void Player::addBall() {
    Ball ball;
    addToVector(ball);
}

// -----------------------------------------------------------------------

void Player::addBall(int posX, int posY, int vX, int vY) {
    Ball ball(posX, posY, vX, vY);
    addToVector(ball);
}

// -----------------------------------------------------------------------

void Player::addToVector(Ball& ball) {
    gBalls.push_back(ball);
}

// -----------------------------------------------------------------------