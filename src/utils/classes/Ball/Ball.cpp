
#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <cmath>
#include <vector>

#include "../../../include/constants.h"

#include "../ImgTexture/ImgTexture.h"

#include "Ball.h"

extern int gMinPoint[];
extern int gScreenSize[];
extern ImgTexture gBalImgTexture;
extern ImgTexture gBallAimTexture;

// -----------------------------------------------------------------------------

Ball::Ball() {}

// -----------------------------------------------------------------------------

Ball::Ball(double vX, double vY) {
    this->vX = vX;
    this->vY = vY;
}

// -----------------------------------------------------------------------------

Ball::Ball(int posX, int posY, double vX, double vY) {
    this->posX = posX;
    this->posY = posY;
    this->vX = vX;
    this->vY = vY;
}

// -----------------------------------------------------------------------------

void Ball::render() {
    gBalImgTexture.render(round(this->posX), round(this->posY));
}

// -----------------------------------------------------------------------------

void Ball::aim() {
    // nesse caso, posX sempre vai ser int, a mira depende da posicao do mouse
    gBallAimTexture.render(this->posX, this->posY);
}

// ------------------------------------------------------------------------------

void Ball::checkCollision(Ball& ball2) {
    std::cout << "[] Getting delta between balls...\n";
    this->getDelta(ball2); // atualiza os valores de distancia entre elas

    if(dx > BALL_DIAMETER || dy > BALL_DIAMETER) return;

    std::cout << "[] Getting center distance between balls...\n";
    if(this->getCenterDistance(dx, dy) <= BALL_DIAMETER){
        std::cout << "[] Balls are colliding...\n";
        this->ballCollision(ball2);
    }
}

// -------------------------------------------------------------------------------

void Ball::wallCollision() {
    if(this->posX + BALL_DIAMETER >= gScreenSize[0] || this->posX <= gMinPoint[0]) {
        std::cout << "[] Ball is colliding horizontally with a wall...\n";
        this->vX = -this->vX;
        std::cout << "[] Flipped horizontal speed...\n";
    }
    if(this->posY + BALL_DIAMETER >= gScreenSize[1] || this->posY <= gMinPoint[1]) {
        std::cout << "[] Ball is colliding vertically with a wall...\n";
        this->vY = -this->vY;
        std::cout << "[] Flipped vertical speed...\n";
    }
}

// -------------------------------------------------------------------------------

int Ball::vSignX() {
    if(this->vX >= 0) return 1;
    return -1;
}

// -------------------------------------------------------------------------------

int Ball::vSignY() {
    if(this->vY >= 0) return 1;
    return -1;
}

// -------------------------------------------------------------------------------

double Ball::collisionAngle(Ball& ball2) {
    return atan2(this->dy, this->dx);
}

// -------------------------------------------------------------------------------

void Ball::getDelta(Ball& ball2) {
    this->dx = this->posX - ball2.posX;
    this->dy = this->posY - ball2.posY;
}

// -------------------------------------------------------------------------------

double Ball::getCenterDistance(int dx, int dy) {
    return sqrt(dx*dx + dy*dy);
}

// -------------------------------------------------------------------------------

void Ball::unstuck(Ball& ball2, double sinTheta, double cosTheta) {

    double intersec = BALL_DIAMETER - this->getCenterDistance(this->dx, this->dy);

    double moveX = intersec*cosTheta/2;
    double moveY = intersec*sinTheta/2;

    this->posX += moveX;
    this->posY += moveY;

    ball2.posX -= moveX;
    ball2.posY -= moveY;
}

// -------------------------------------------------------------------------------

void Ball::ballCollision(Ball& ball2) {

    double theta = this->collisionAngle(ball2);

    double sinTheta = sin(theta);
    double cosTheta = cos(theta);

    this->unstuck(ball2, sinTheta, cosTheta);
    
    // rotacionando o eixo pra fazer uma colisao 1D
    double vx1 = this->vX*cosTheta + this->vY*sinTheta;
    double vx2 = ball2.vX*cosTheta + ball2.vY*sinTheta;

    double vy1 = -this->vX*sinTheta + this->vY*cosTheta;
    double vy2 = -ball2.vX*sinTheta + ball2.vY*cosTheta;

    std::swap(vx1, vx2); // colisao 1D, eixo y' nao interfere

    // voltando o eixo
    this->vX = vx1*cosTheta - vy1*sinTheta;
    this->vY = vx1*sinTheta + vy1*cosTheta;

    ball2.vX = vx2*cosTheta - vy2*sinTheta;
    ball2.vY = vx2*sinTheta + vy2*cosTheta;
}

// -------------------------------------------------------------------------------
