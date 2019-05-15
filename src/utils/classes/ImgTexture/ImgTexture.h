
#ifndef IMGTEX_H_
#define IMGTEX_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <string>

class ImgTexture
{
    public:

        SDL_Texture* sdltexture;

        int width;
        int height;

        ImgTexture();

        ~ImgTexture();

        void free();

        // path relativo a onde ta sendo executado o compilado
        bool loadImg(std::string path);

        bool loadText(std::string text, TTF_Font* font, SDL_Color textColor);

        void updateText(int posX, int posY, TTF_Font* font, std::string text, SDL_Color textColor);

        void setColor(Uint8 red, Uint8 green, Uint8 blue);

        void setBlendMode(SDL_BlendMode blendMode);

        void setAlpha(Uint8 alpha);

        void render(int posX, int posY,
                    SDL_Rect* clip = nullptr, double angle = 0.0,
                    SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

};

#endif