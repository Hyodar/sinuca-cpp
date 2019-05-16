
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>
#include <string>

#include "./ImgTexture.h"

extern SDL_Renderer* gRenderer;
extern TTF_Font* gFont;

// ------------------------------------------------------------------

ImgTexture::ImgTexture() {
    this->sdltexture = nullptr;
    
    this->width = 0;
    this->height = 0;
}

// -------------------------------------------------------------------

ImgTexture::~ImgTexture() {
    this->free();
}

// --------------------------------------------------------------------

void ImgTexture::free() {
    if(this->sdltexture != nullptr) {
        
        SDL_DestroyTexture(this->sdltexture);
        this->sdltexture = nullptr;
        
        this->width = 0;
        this->height = 0;
    }
}

// ---------------------------------------------------------------------

bool ImgTexture::loadImg(std::string path) {

    this->free();

    SDL_Texture* newTexture = nullptr;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if(loadedSurface == nullptr) {
        std::cout << "[] Image '" << path.c_str() << "' load error: " << SDL_GetError() << "\n";
    }
    else {
        
        SDL_SetColorKey(loadedSurface,
                        SDL_TRUE,
                        SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

        if(newTexture == nullptr) {
            std::cout << "Unable to create texture from '" << path.c_str() <<"'\n";
        } else {
            this->width = loadedSurface->w;
            this->height = loadedSurface->h;
        }

        SDL_FreeSurface(loadedSurface);
    }

    this->sdltexture = newTexture;
    return this->sdltexture != nullptr;
}

// ---------------------------------------------------------------------

bool ImgTexture::loadText(std::string text, TTF_Font* font, SDL_Color textColor) {
    this->free();

    SDL_Texture* newTexture = nullptr;

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);

    if(textSurface != nullptr) {
        newTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);

        if(newTexture == nullptr) {
            std::cout << "Unable to create texture from text! Error: " << SDL_GetError() << "\n";
        }
        else {
            this->width = textSurface->w;
            this->height = textSurface->h;
        }

        SDL_FreeSurface(textSurface);
    }

    this->sdltexture = newTexture;
    return newTexture != nullptr;
}

// ---------------------------------------------------------------------

void ImgTexture::updateText(int posX, int posY, TTF_Font* font, std::string text, SDL_Color textColor) {
    this->loadText(text, font, textColor);
    this->render(posX, posY);
}

// ---------------------------------------------------------------------

void ImgTexture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
    SDL_SetTextureColorMod(this->sdltexture, red, green, blue);
}

// ---------------------------------------------------------------------

void ImgTexture::setBlendMode(SDL_BlendMode blending) {
    SDL_SetTextureBlendMode(this->sdltexture, blending);
}

// ---------------------------------------------------------------------

void ImgTexture::render(int posX, int posY, SDL_Rect* clip, double angle,
                         SDL_Point* center, SDL_RendererFlip flip) 
{
    SDL_Rect renderQuad = {posX, posY, this->width, this->height};

    if(clip != nullptr) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx(gRenderer, this->sdltexture, clip, &renderQuad,
                    angle, center, flip);
}

// ---------------------------------------------------------------------
