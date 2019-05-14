
#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <vector>

#include "../../../include/constants.h"

#include "../Ball/Ball.h"
#include "../LTexture/LTexture.h"
#include "../MovementSystem/MovementSystem.h"
#include "../CollisionSystem/CollisionSystem.h"

#include "Project.h"

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern LTexture gBallTexture;
extern MovementSystem gMovement;
extern CollisionSystem gCollision;
extern std::vector<Ball> gBalls;
extern Ball gAim;
extern int gScreenSize[];

// -------------------------------------------------------------------------

void Project::init() {
    gWindow = SDL_CreateWindow(
                    DEFAULT_WINDOW_NAME,
                    SDL_WINDOWPOS_UNDEFINED,
                    SDL_WINDOWPOS_UNDEFINED,
                    gScreenSize[0],
                    gScreenSize[1],
                    SDL_WINDOW_SHOWN);

    if(!gWindow) {
        std::cout << "Erro: Window não foi inicializada corretamente: " << SDL_GetError();
        throw -1;
    } else {
        std::cout << "[] Window initialized...\n";
    }

    gRenderer = SDL_CreateRenderer(
                    gWindow,
                    -1,
                    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!gRenderer) {
        std::cout << "Erro: Renderer não foi inicializada corretamente: " << SDL_GetError();
        throw -1;
    } else {
        std::cout << "[] Renderer initialized...\n";
    }

    SDL_SetRenderDrawColor(gRenderer, 0x0, 0xFF, 0x0, 0xFF);

    IMG_Init(IMG_INIT_PNG);

    std::cout << "[] Image module initialized...\n";

    bool openedTexture = gBallTexture.loadFromFile("resources/images/ball.png");
    
    if(!openedTexture) std::cout << "Could not open ball texture!\n";
    else std::cout << "[] Ball texture opened...\n";
}

// -------------------------------------------------------------------------

void Project::close() {
    gBallTexture.free();

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);

    gRenderer = NULL;
    gWindow = NULL;
    
    SDL_Quit();
    IMG_Quit();
}

// -------------------------------------------------------------------------

void Project::renderAll() {
    gMovement.process();
    std::cout << "[] Movement events processed...\n";

    gCollision.process();
    std::cout << "[] Collision events processed...\n";

    SDL_RenderClear(gRenderer);
    std::cout << "[] Rendered clear...\n";

    for(Ball& ball: gBalls) {
        ball.render();
    }
    std::cout << "[] Rendered new ball positions...\n";

    //gAim.render();

    SDL_RenderPresent(gRenderer);
    std::cout << "[] Rendered present...\n";

    SDL_Delay(10);
    std::cout << "[] SDL Delay...";
}