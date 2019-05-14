
#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <vector>

using namespace std;

#include "./include/constants.h"

#include "./utils/classes/Ball/Ball.h"
#include "./utils/classes/Player/Player.h"
#include "./utils/classes/Project/Project.h"
#include "./utils/classes/LTexture/LTexture.h"
#include "./utils/classes/MovementSystem/MovementSystem.h"
#include "./utils/classes/CollisionSystem/CollisionSystem.h"

// Variaveis globais (g para indicar global)
// --------------------------------------------------------------------

// TODO: colocar forma de escolher dimensoes da janela e numero inicial de bolas

SDL_Window *gWindow = nullptr; // janela do jogo
SDL_Renderer *gRenderer = nullptr; // renderer

MovementSystem gMovement; // sistema pra processar o movimento das bolas
CollisionSystem gCollision; // sistema pra processar a colisao das bolas

std::vector<Ball> gBalls; // vetor das bolas presentes
Ball gAim; // cursor do mouse

LTexture gBallTexture;
LTexture gBallAimTexture;

int gMinPoint[] = {DEFAULT_MIN_X, DEFAULT_MIN_Y};
int gScreenSize[2] = {DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT};

// ---------------------------------------------------------------------

int main(int argc, char* args[]) {

    Project project;
    Player player;

    project.init();

    bool quit = false;
    SDL_Event e;

    player.addBall(0,0,2,3);
    std::cout << "[] Player added a ball...\n";

    player.addBall(200,400,-1,5);
    std::cout << "[] Player added a ball...\n";

    int mouseClickX = 0;
    int mouseClickY = 0;

    int mousePosX = 0;
    int mousePosY = 0;

    bool aiming = false;

    while(!quit) {

        while(SDL_PollEvent(&e) != 0) {

            switch(e.type) 
            {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_MOUSEMOTION:

                    if(aiming) {
                        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                        SDL_RenderDrawLine(gRenderer, mouseClickX, mouseClickY, e.motion.x, e.motion.y);
                    } else {
                        gAim.posX = e.motion.x - BALL_RADIUS;
                        gAim.posY = e.motion.y - BALL_RADIUS;
                    }

                    break;
                case SDL_MOUSEBUTTONDOWN:
                    aiming = true;
                    mouseClickX = e.button.x;
                    mouseClickY = e.button.y;
                    break;
                case SDL_MOUSEBUTTONUP:
                    aiming = false;
                    player.throwBall(mouseClickX, mouseClickY, e.button.x, e.button.y);
                    break;
            }

        }

        std::cout << "[] Processing window changes...\n";

        project.renderAll();
    }

    project.close();

}



