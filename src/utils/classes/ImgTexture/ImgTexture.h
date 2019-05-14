
#ifndef IMGTEX_H_
#define IMGTEX_H_

#include <SDL.h>
#include <SDL_image.h>

#include <string>

class ImgTexture
{
    public:

        SDL_Texture* sdImgTexture;

        int width;
        int height;

        ImgTexture();

        ~ImgTexture();

        void free();

        // path relativo a onde ta sendo executado o compilado
        bool loadImg(std::string path);

        void setColor(Uint8 red, Uint8 green, Uint8 blue);

        void setBlendMode(SDL_BlendMode blendMode);

        void setAlpha(Uint8 alpha);

        void render(int posX, int posY,
                    SDL_Rect* clip = nullptr, double angle = 0.0,
                    SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

};

#endif