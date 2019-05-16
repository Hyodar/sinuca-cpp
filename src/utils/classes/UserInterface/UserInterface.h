
#ifndef UI_H_
#define UI_H_

// botao de pause
// botao de play

extern int gScreenSize[];

class UserInterface
{
    public:

        int menuPos[2] = {gScreenSize[0] - UI_WIDTH, gScreenSize[1] - UI_HEIGHT};
        
        int pausePos[2] = {this->menuPos[0] + BUTTON_SIZE, this->menuPos[1] + BUTTON_SIZE};
        int playPos[2] = {this->menuPos[0] + 2*BUTTON_SIZE + 10, this->menuPos[1] + BUTTON_SIZE};

        void init();

        void render();

        void updatePositions();

        bool clickedPause();

        bool clickedPlay();

        bool checkClicks();

    private:

        void renderPause();

        void renderPlay();
};

#endif
