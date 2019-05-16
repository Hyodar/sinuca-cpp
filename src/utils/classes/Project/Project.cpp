
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>
#include <string>
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

extern TTF_Font* gFont;
extern TTF_Font* gFontBig;

extern bool gAiming;

extern MovementSystem gMovement;
extern CollisionSystem gCollision;
extern UserInterface gUserInterface;

extern Player gPlayer;

extern std::vector<Ball> gBalls;
extern Ball gAim;

extern bool gIsPlaying;

extern int gScreenSize[];

// -------------------------------------------------------------------------

void Project::configWindow() {

    gWindow = SDL_CreateWindow(
                    DEFAULT_WINDOW_NAME,
                    SDL_WINDOWPOS_CENTERED,
                    SDL_WINDOWPOS_CENTERED,
                    DEFAULT_CONFIG_WINDOW_WIDTH,
                    DEFAULT_CONFIG_WINDOW_HEIGHT,
                    SDL_WINDOW_SHOWN);

    gRenderer = SDL_CreateRenderer(
                    gWindow,
                    -1,
                    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
                );

    SDL_SetRenderDrawColor(gRenderer,
                            DEFAULT_BG_COLOR[0],
                            DEFAULT_BG_COLOR[1],
                            DEFAULT_BG_COLOR[2],
                            DEFAULT_BG_COLOR[4]);

    SDL_RenderClear(gRenderer);

    std::cout << "Setting up config window...\n";

    bool quit = false;
    SDL_Event e;

    std::string inputText = "";
    int inputCount = 0;
    std::vector <std::string> inputs;
    std::vector <std::string> questions = {"Insira a largura em px: ",
                                         "Insira a altura em px: ",
                                         "Insira o número de bolas inicial: ",
                                         ""};
    
    ImgTexture textbox;
    ImgTexture questionText;

    SDL_StartTextInput();

    while(!quit) {
        while(SDL_PollEvent(&e) != 0) {
            switch(e.type) {
                case SDL_KEYDOWN:
                    if((e.key.keysym.sym == SDLK_BACKSPACE) && inputText.length() > 0) {
                        inputText.pop_back();
                        break;
                    }
                    if(e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_KP_ENTER) {
                        
                        inputs.push_back(inputText);
                        inputText = "";
                        
                        ++inputCount;

                        if(inputCount == 3) {
                            quit = true;
                        }
                    }
                    break;
                case SDL_TEXTINPUT:
                    inputText += e.text.text;
                    break;
                case SDL_QUIT:
                    quit = true;
                    break;
            }
        }
        SDL_RenderClear(gRenderer);
        
        if(inputText != "") {
            textbox.updateText(150, 150, gFontBig, inputText, WHITE);
        }
        questionText.updateText(100, 50, gFontBig, questions[inputCount], BLACK);

        SDL_RenderPresent(gRenderer);
        SDL_Delay(10);
    }

    end:
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);

    if(inputCount == 3) {
        this->processGameConfig(inputs);
    } else {
        throw -1;
    }
}

// -------------------------------------------------------------------------

void Project::processGameConfig(std::vector<std::string> inputs) {

    int screenW = std::stoi(inputs[0]);
    int screenH = std::stoi(inputs[1]);
    int nBalls = std::stoi(inputs[2]);

    if(screenW < UI_WIDTH) {
        std::cout << "[!] Invalid width input - using default value...\n";
        screenW = DEFAULT_SCREEN_WIDTH;
    }

    if(screenH < UI_HEIGHT) {
        std::cout << "[!] Invalid height input - using default value...\n";
        screenH = DEFAULT_SCREEN_HEIGHT;
    }

    gScreenSize[0] = screenW;
    gScreenSize[1] = screenH;
    gPlayer.randomBalls(nBalls);
}

// -------------------------------------------------------------------------

void Project::init() {

    TTF_Init();

    gFont = TTF_OpenFont("resources/fonts/OpenSans-Regular.ttf", DEFAULT_FONT_SIZE);
    gFontBig = TTF_OpenFont("resources/fonts/OpenSans-Regular.ttf", DEFAULT_FONT_SIZE_BIG);
    std::cout << "[] Loaded OpenSans...\n";

    this->configWindow();

    // Jogador seta as configurações do jogo
    //gPlayer.setGameConfig();

    // Cria janela
    gWindow = SDL_CreateWindow(
                    DEFAULT_WINDOW_NAME,
                    SDL_WINDOWPOS_CENTERED,
                    SDL_WINDOWPOS_CENTERED,
                    gScreenSize[0],
                    gScreenSize[1],
                    SDL_WINDOW_SHOWN);

    if(!gWindow) {
        std::cout << "[!] Error while creating window: " << SDL_GetError();
        throw -1;
    }
    std::cout << "[] Window initialized...\n";
    
    // Cria renderer
    gRenderer = SDL_CreateRenderer(
                    gWindow,
                    -1,
                    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!gRenderer) {
        std::cout << "[!] Error while creating renderer: " << SDL_GetError();
        throw -1;
    }
    std::cout << "[] Renderer initialized...\n";

    // Cor da background
    SDL_SetRenderDrawColor(gRenderer,
                            DEFAULT_BG_COLOR[0],
                            DEFAULT_BG_COLOR[1],
                            DEFAULT_BG_COLOR[2],
                            DEFAULT_BG_COLOR[4]);
                        
    // Iniciando o módulo de imagens
    if(IMG_Init(IMG_INIT_PNG) == NULL) {
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

    if(!gIsPlaying) {
        ImgTexture textPaused;
        textPaused.loadText("Paused", gFontBig, WHITE);
        textPaused.render(gScreenSize[0]/2 - textPaused.width/2, gScreenSize[1]/2 - textPaused.height/2);
    }

    gAim.aim();

    if(gAiming) gPlayer.drawLine();

    gUserInterface.render();

    SDL_RenderPresent(gRenderer);
    std::cout << "[] Rendered present...\n";

    SDL_Delay(10);
    std::cout << "[] SDL Delay...\n";
}

// -------------------------------------------------------------------------