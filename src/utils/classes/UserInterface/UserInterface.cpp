
#include <STD.h>
#include <STD_image.h>

#include "../../../include/constants.h"

#include "../ImgTexture/ImgTexture.h"

#include "UserInterface.h"

extern bool gIsPlaying;
extern int gScreenSize[];

extern SDL_Renderer* gRenderer;

extern ImgTexture gPlayBtnTexture;
extern ImgTexture gPauseBtnTexture;

extern int gMouseClickX;
extern int gMouseClickY;


// -----------------------------------------------------------------------

void UserInterface::init() {
    gPlayBtnTexture.loadImg("resources/images/playbtn.png");
    gPauseBtnTexture.loadImg("resources/images/pausebtn.png");
}

// -----------------------------------------------------------------------

void UserInterface::render() {

    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 100);
    SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);

    SDL_Rect menu = {this->menuPos[0], this->menuPos[1], UI_WIDTH, UI_HEIGHT};

    SDL_RenderFillRect(gRenderer, &menu);

    this->renderPause();
    this->renderPlay();
}

// ------------------------------------------------------------------------

bool UserInterface::checkClicks() {
    if(this->clickedPause()) {
        gIsPlaying = false;
        return true;
    }
    if(this->clickedPlay()) {
        gIsPlaying = true;
        return true;
    }
    return false;
}

// ------------------------------------------------------------------------

void UserInterface::renderPause() {
    gPauseBtnTexture.render(this->pausePos[0], this->pausePos[1]);
}

// ------------------------------------------------------------------------

void UserInterface::renderPlay() {
    gPlayBtnTexture.render(this->playPos[0], this->playPos[1]);
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
