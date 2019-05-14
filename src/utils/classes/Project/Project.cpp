
#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <vector>

#include "../../../include/constants.h"

#include "../Ball/Ball.h"
#include "../Player/Player.h"
#include "../LTexture/LTexture.h"
#include "../MovementSystem/MovementSystem.h"
#include "../CollisionSystem/CollisionSystem.h"

#include "Project.h"

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

extern LTexture gBallTexture;
extern LTexture gBallAimTexture;
extern bool gAiming;

extern MovementSystem gMovement;
extern CollisionSystem gCollision;

extern Player gPlayer;

extern std::vector<Ball> gBalls;
extern Ball gAim;

extern int gScreenSize[];

// -------------------------------------------------------------------------

void Project::init() {
    // Jogador seta as configurações do jogo
    gPlayer.setGameConfig();

    // Cria janela
    gWindow = SDL_CreateWindow(
                    DEFAULT_WINDOW_NAME,
                    SDL_WINDOWPOS_UNDEFINED,
                    SDL_WINDOWPOS_UNDEFINED,
                    gScreenSize[0],
                    gScreenSize[1],
                    SDL_WINDOW_SHOWN);

    if(!gWindow) {
        std::cout << "[!] Error while creating window: " << SDL_GetError();
        throw -1;
    } else {
        std::cout << "[] Window initialized...\n";
    }

    // Cria renderer
    gRenderer = SDL_CreateRenderer(
                    gWindow,
                    -1,
                    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!gRenderer) {
        std::cout << "[!] Error while creating renderer: " << SDL_GetError();
        throw -1;
    } else {
        std::cout << "[] Renderer initialized...\n";
    }

    // Cor da background
    SDL_SetRenderDrawColor(gRenderer,
                            DEFAULT_BG_COLOR[0],
                            DEFAULT_BG_COLOR[1],
                            DEFAULT_BG_COLOR[2],
                            DEFAULT_BG_COLOR[4]);
                        
    // Iniciando o módulo de imagens
    IMG_Init(IMG_INIT_PNG);

    std::cout << "[] Image module initialized...\n";

    bool openedBallTexture = gBallTexture.loadFromFile("resources/images/ball.png");
    
    if(!openedBallTexture) std::cout << "[!] Could not open ball texture!\n";
    else std::cout << "[] Ball texture opened...\n";

    bool openedAimTexture = gBallAimTexture.loadFromFile("resources/images/ball_aim.png");
    
    if(!openedAimTexture) std::cout << "[!] Could not open ball aim texture!\n";
    else std::cout << "[] Ball aim texture opened...\n";

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
    
    if(gAiming) {
        gPlayer.drawLine();
    }
    else {
        gMovement.process();
        std::cout << "[] Movement events processed...\n";

        gCollision.process();
        std::cout << "[] Collision events processed...\n";
    }

    SDL_SetRenderDrawColor(gRenderer,
                            DEFAULT_BG_COLOR[0],
                            DEFAULT_BG_COLOR[1],
                            DEFAULT_BG_COLOR[2],
                            DEFAULT_BG_COLOR[4]);

    SDL_RenderClear(gRenderer);
    std::cout << "[] Rendered clear...\n";

    for(Ball& ball: gBalls) {
        ball.render();
    }
    std::cout << "[] Rendered new ball positions...\n";

    gAim.aim();

    SDL_RenderPresent(gRenderer);
    std::cout << "[] Rendered present...\n";

    SDL_Delay(10);
    std::cout << "[] SDL Delay...\n";
}