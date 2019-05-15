
#ifndef UI_H_
#define UI_H_

// botao de pause
// botao de play

#include "../../../include/constants.h"

class UserInterface
{
    public:

        const int menuPos[] = {gScreenSize[0] - UI_WIDTH, gScreenSize[1] - UI_HEIGHT};
        
        const int pausePos[] = {this->menuPos[0] + BUTTON_SIZE, this->menuPos[1] + BUTTON_SIZE};
        const int playPos[] = {this->menuPos[0] + BUTTON_SIZE + 10, this->menuPos[1] + BUTTON_SIZE};

        void init();

        void render();

        bool clickedPause();

        bool clickedPlay();

        bool checkClicks();

    private:

        void renderPause();

        void renderPlay();
};

#endif
