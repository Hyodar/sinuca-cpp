
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>
#include <vector>

#include "../../../include/constants.h"

#include "../Ball/Ball.h"
#include "../Player/Player.h"
#include "../ImgTexture/ImgTexture.h"
#include "../MovementSystem/MovementSystem.h"
#include "../CollisionSystem/CollisionSystem.h"
#include "../UserInterface/UserInterface.h"

#include "Project.h"

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

extern ImgTexture gBalImgTexture;
extern ImgTexture gBallAimTexture;
extern bool gAiming;

extern MovementSystem gMovement;
extern CollisionSystem gCollision;
extern UserInterface gUserInterface;

extern Player gPlayer;

extern std::vector<Ball> gBalls;
extern Ball gAim;

extern int gScreenSize[];

// -------------------------------------------------------------------------

void Project::init() {
    // Jogador seta as configurações do jogo
    gPlayer.setGameConfig();

    SDL_Init();

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
    if(IMG_Init(IMG_INIT_PNG) == nullptr) {
        std::cout << "[!] Failed to initialize image module...\n";
        throw -1;
    }

    std::cout << "[] Image module initialized...\n";

    bool openedBalImgTexture = gBalImgTexture.loadImg("resources/images/ball.png");
    
    if(!openedBalImgTexture) std::cout << "[!] Could not open ball texture!\n";
    else std::cout << "[] Ball texture opened...\n";

    bool openedAimTexture = gBallAimTexture.loadImg("resources/images/ball_aim.png");
    
    if(!openedAimTexture) std::cout << "[!] Could not open ball aim texture!\n";
    else std::cout << "[] Ball aim texture opened...\n";

    gUserInterface.init();

    if(TTF_Init() != nullptr) {
        std::cout << "[!] Failed to initialize font module...\n";
        throw -1;
    }

}

// -------------------------------------------------------------------------

void Project::close() {
    gBalImgTexture.free();

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);

    gRenderer = NULL;
    gWindow = NULL;
    
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}

// -------------------------------------------------------------------------

void Project::renderAll() {
    if(gIsPlaying) {
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

    if(gAiming) gPlayer.drawLine();

    gUserInterface.render();

    SDL_RenderPresent(gRenderer);
    std::cout << "[] Rendered present...\n";

    SDL_Delay(10);
    std::cout << "[] SDL Delay...\n";
}

// -------------------------------------------------------------------------