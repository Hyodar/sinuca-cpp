
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

SDL_Window *gWindow = nullptr; // janela do jogo
SDL_Renderer *gRenderer = nullptr; // renderer

MovementSystem gMovement; // sistema pra processar o movimento das bolas
CollisionSystem gCollision; // sistema pra processar a colisao das bolas

std::vector<Ball> gBalls; // vetor das bolas presentes
Ball gAim; // cursor do mouse

LTexture gBallTexture;

int gMinPoint[] = {DEFAULT_MIN_X, DEFAULT_MIN_Y};
int gScreenSize[2] = {DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT};

// ---------------------------------------------------------------------

// Classe Project já declarada em src/utils/classes
// Classe Player já declarada em src/utils/classes
// Classe MovementSystem já declarada em src/utils/classes
// Classe CollisionSystem já declarada em src/utils/classes
// Classe Ball já declarada em src/utils/classes


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

    while(!quit) {

        while(SDL_PollEvent(&e) != 0) {

            switch(e.type) 
            {
                case SDL_QUIT:
                    quit = true;
                    break;

            }

        }

        std::cout << "[] Processing window changes...\n";

        project.renderAll();
    }

    project.close();

}



