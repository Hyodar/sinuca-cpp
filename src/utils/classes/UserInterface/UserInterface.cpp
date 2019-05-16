
#include <SDL.h>
#include <SDL_image.h>

#include <iostream>

#include "../Player/Player.h"
#include "../ImgTexture/ImgTexture.h"

#include "../../../include/constants.h"

#include "UserInterface.h"

extern Player gPlayer;

extern bool gIsPlaying;
extern int gScreenSize[];

extern SDL_Renderer* gRenderer;

extern int gMouseClickX;
extern int gMouseClickY;

/*
extern int UI_WIDTH;
extern int UI_HEIGHT;
extern int BUTTON_SIZE;
*/
// -----------------------------------------------------------------------

void UserInterface::init() {
    this->playBtnTexture.loadImg("resources/images/playbtn.png");
    this->pauseBtnTexture.loadImg("resources/images/pausebtn.png");
    this->replayBtnTexture.loadImg("resources/images/replaybtn.png");
}

// -----------------------------------------------------------------------

void UserInterface::render() {

    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 100);
    SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);

    SDL_Rect menu = {this->menuPos[0], this->menuPos[1], UI_WIDTH, UI_HEIGHT};

    // Renderizacao do menu e botoes
    SDL_RenderFillRect(gRenderer, &menu);

    this->renderPause();
    this->renderPlay();
    this->renderReplay();
}

// ------------------------------------------------------------------------

void UserInterface::updatePositions() {
    this->menuPos[0] = gScreenSize[0] - UI_WIDTH;
    this->menuPos[1] = gScreenSize[1] - UI_HEIGHT;

    this->pausePos[0] = this->menuPos[0] + BUTTON_SIZE;
    this->pausePos[1] = this->menuPos[1] + BUTTON_SIZE/2;

    this->playPos[0] = this->pausePos[0] + BUTTON_SIZE +UI_PADDING;
    this->playPos[1] = this->pausePos[1];

    this->replayPos[0] = this->playPos[0] + BUTTON_SIZE + UI_PADDING;
    this->replayPos[1] = this->pausePos[1];
}

// ------------------------------------------------------------------------

bool UserInterface::checkClicks() {
    if(this->clickedPause()) {
        std::cout << "[] Player clicked play...\n";
        gIsPlaying = false;
        return true;
    }
    if(this->clickedPlay()) {
        std::cout << "[] Player clicked pause...\n";
        gIsPlaying = true;
        return true;
    }
    if(this->clickedReplay()){
        std::cout << "[] Player clicked replay...\n";
        gPlayer.resetGame();
        return true;
    }
    return false;
}

// ------------------------------------------------------------------------

void UserInterface::renderPause() {
    this->pauseBtnTexture.render(this->pausePos[0], this->pausePos[1]);
}

// ------------------------------------------------------------------------

void UserInterface::renderPlay() {
    this->playBtnTexture.render(this->playPos[0], this->playPos[1]);
}

// ------------------------------------------------------------------------

void UserInterface::renderReplay() {
    this->replayBtnTexture.render(this->replayPos[0], this->replayPos[1]);
}

// ------------------------------------------------------------------------

bool UserInterface::clickedPause() {
    return gMouseClickX >= this->pausePos[0] &&
           gMouseClickX <= (this->pausePos[0] + BUTTON_SIZE) &&
           gMouseClickY >= this->pausePos[1] &&
           gMouseClickY <= (this->pausePos[1] + BUTTON_SIZE);
}

// ------------------------------------------------------------------------

bool UserInterface::clickedPlay() {
    return gMouseClickX >= this->playPos[0] &&
           gMouseClickX <= (this->playPos[0] + BUTTON_SIZE) &&
           gMouseClickY >= this->playPos[1] &&
           gMouseClickY <= (this->playPos[1] + BUTTON_SIZE);
}

// ------------------------------------------------------------------------

bool UserInterface::clickedReplay() {
    return gMouseClickX >= this->replayPos[0] &&
           gMouseClickX <= (this->replayPos[0] + BUTTON_SIZE) &&
           gMouseClickY >= this->replayPos[1] &&
           gMouseClickY <= (this->replayPos[1] + BUTTON_SIZE);
}

// ------------------------------------------------------------------------
