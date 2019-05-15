
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

ImgTexture gBalImgTexture; // textura da img da bola
ImgTexture gBallAimTexture; // textura da img da mira

// mantem o ultimo clique e a posicao do mouse pra usos variados
int gMouseClickX;
int gMouseClickY;

int gMouseMotionX;
int gMouseMotionY;

// entidade Player, implementa o que é usado pelo jogador
Player gPlayer;

// ponto minimo e maximo da tela
// o ponto mínimo é útil pra não ter que mudar todo o código se tiver alguma parte de ui em cima
int gMinPoint[] = {DEFAULT_MIN_X, DEFAULT_MIN_Y};
int gScreenSize[2] = {DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT};

// ---------------------------------------------------------------------

int main(int argc, char* args[]) {

    // entidade Project, implementa as funcoes de inicializaçao e processamento interno da simulacao
    Project project;

    // inicializa janela, renderer, etc
    project.init();

    bool quit = false;
    SDL_Event e;

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
                        // so move a mira se n estiver mirando uma bola para jogar
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

        // processa tudo: o sistema de movimentacao, colisao, renderizacao, etc
        project.renderAll();
    }

    // destroi as instancias criadas pelo projeto e chama a funcao de fechamento do SDL
    project.close();

    return 0;
}



