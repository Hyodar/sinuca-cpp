
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

Ball::Ball(int vX, int vY) {
    this->vX = vX;
    this->vY = vY;
}

// -----------------------------------------------------------------------------

Ball::Ball(int posX, int posY, int vX, int vY) {
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

   /*
    // isso n deve estar funcionando
    double posX1 = this->posX*cosTheta + this->posY*sinTheta;
    double posX2 = ball2.posX*cosTheta + ball2.posY*sinTheta;

    double posY1 = -this->posX*sinTheta + this->posY*cosTheta;
    double posY2 = -ball2.posX*sinTheta + ball2.posY*cosTheta;

    double intersec = BALL_DIAMETER - (posX2 - posX1);

    posX1 += ceil(intersec/2);
    posX2 -= ceil(intersec/2);

    this->posX = posX1*cosTheta - posY1*sinTheta;
    this->posY = posX1*sinTheta + posY1*cosTheta;

    ball2.posX = posX2*cosTheta - posY2*sinTheta;
    ball2.posY = posX2*sinTheta + posY2*cosTheta;
    */
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
