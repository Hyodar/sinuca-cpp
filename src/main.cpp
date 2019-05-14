
#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <vector>

using namespace std;

#include "./include/constants.h"

#include "./utils/classes/Ball/Ball.h"
#include "./utils/classes/Player/Player.h"
#include "./utils/classes/Project/Project.h"
#include "./utils/classes/ImgTexture/ImgTexture.h"
#include "./utils/classes/MovementSystem/MovementSystem.h"
#include "./utils/classes/CollisionSystem/CollisionSystem.h"

// Variaveis globais (g para indicar global)
// --------------------------------------------------------------------

SDL_Window *gWindow = nullptr; // janela do jogo
SDL_Renderer *gRenderer = nullptr; // renderer

MovementSystem gMovement; // sistema pra processar o movimento das bolas
CollisionSystem gCollision; // sistema pra processar a colisao das bolas

std::vector<Ball> gBalls; // vetor das bolas presentes
Ball gAim; // cursor do mouse
bool gAiming = false;

ImgTexture gBalImgTexture;
ImgTexture gBallAimTexture;

int gMouseClickX;
int gMouseClickY;

int gMouseMotionX;
int gMouseMotionY;

Player gPlayer;

int gMinPoint[] = {DEFAULT_MIN_X, DEFAULT_MIN_Y};
int gScreenSize[2] = {DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT};

// ---------------------------------------------------------------------

int main(int argc, char* args[]) {

    Project project;

    project.init();

    bool quit = false;
    SDL_Event e;

    int mouseClickX = 0;
    int mouseClickY = 0;

    bool aiming = false;

    while(!quit) {

        while(SDL_PollEvent(&e) != 0) {

            switch(e.type) 
            {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_MOUSEMOTION:
                    gMouseMotionX = e.motion.x;
                    gMouseMotionY = e.motion.y;

                    if(!gAiming) {
                        gAim.posX = gMouseMotionX - BALL_RADIUS;
                        gAim.posY = gMouseMotionY - BALL_RADIUS;
                    }

                    break;
                case SDL_MOUSEBUTTONDOWN:
                    gAiming = true;
                    gMouseClickX = e.button.x;
                    gMouseClickY = e.button.y;
                    break;
                case SDL_MOUSEBUTTONUP:
                    gAiming = false;
                    gPlayer.throwBall();
                    break;
            }

        }

        std::cout << "[] Processing window changes...\n";

        project.renderAll();
    }

    project.close();

}



