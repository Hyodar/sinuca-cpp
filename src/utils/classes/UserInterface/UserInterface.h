
#ifndef UI_H_
#define UI_H_

// botao de pause
// botao de play

extern int gScreenSize[];

class UserInterface
{
    public:

        int menuPos[2];
        
        int pausePos[2];
        int playPos[2];
        int replayPos[2];

        void init();

        void render();

        void updatePositions();

        bool clickedPause();

        bool clickedPlay();
        
        bool clickedReplay();

        bool checkClicks();

    private:

        ImgTexture playBtnTexture;
        ImgTexture pauseBtnTexture;
        ImgTexture replayBtnTexture;

        void renderPause();

        void renderPlay();

        void renderReplay();
};

#endif
