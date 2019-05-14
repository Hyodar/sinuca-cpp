
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "../../../include/constants.h"

#include "../Ball/Ball.h"

#include "Player.h"

extern std::vector<Ball> gBalls;
extern int gScreenSize[];
extern int gMinPoint[];

// -----------------------------------------------------------------------

void Player::setGameConfig() {
    int nBalls;

    std::cout << "Largura da tela (em px): ";
    std::cin >> gScreenSize[0];
    
    if(std::cin.fail()) {
        std::cout << "[] Invalid input - using default value...";
        gScreenSize[0] = DEFAULT_SCREEN_WIDTH;
        std::cin.clear(); // reseta a flag fail do cin
    }

    std::cout << "Altura da tela (em px): ";
    std::cin >> gScreenSize[1];

    if(std::cin.fail()) {
        std::cout << "[] Invalid input - using default value...";
        gScreenSize[1] = DEFAULT_SCREEN_HEIGHT;
        std::cin.clear(); // reseta a flag fail do cin
    }

    std::cout << "Numero inicial de bolas: ";
    std::cin >> nBalls;

    if(std::cin.fail()) {
        std::cout << "[] Invalid input - using default value...";
        nBalls = DEFAULT_BALL_COUNT;
        std::cin.clear(); // reseta a flag fail do cin
    }

    std::cout << "\n";

    this->randomBalls(nBalls);
}

// -----------------------------------------------------------------------

void Player::addBall(int posX, int posY, int vX, int vY) {
    Ball ball(posX, posY, vX, vY);
    addToVector(ball);
}

// -----------------------------------------------------------------------

void Player::throwBall(int mouseClickX, int mouseClickY, int mouseUpX, int mouseUpY) {
    Ball ball  (mouseClickX - BALL_RADIUS,
                mouseClickY - BALL_RADIUS,
                (mouseClickX - mouseUpX)/PINCH_FACTOR,
                (mouseClickY - mouseUpY)/PINCH_FACTOR);
    addToVector(ball);
}

// -----------------------------------------------------------------------

void Player::randomBalls(int nBalls) {
    srand(time(NULL));

    for(int i=0; i<nBalls; i++) {
        Ball ball  ((rand() % (gScreenSize[0] - gMinPoint[0])) + gMinPoint[0],
                    (rand() % (gScreenSize[1] - gMinPoint[1])) + gMinPoint[1],
                    (rand() % 2*DEFAULT_RAND_VEL_RNG) - DEFAULT_RAND_VEL_RNG,
                    (rand() % 2*DEFAULT_RAND_VEL_RNG) - DEFAULT_RAND_VEL_RNG);
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

void Player::drawLine(int mouseClickX, int mouseClickY, int mouseMotionX, int mouseMotionY) {
    
}

// -----------------------------------------------------------------------