
#include <SDL.h>
#include <SDL_image.h>

#include <string>

#include "./ImgTexture.h"

extern SDL_Renderer* gRenderer;

// ------------------------------------------------------------------

ImgTexture::ImgTexture() {
    this->sdImgTexture = nullptr;
    
    this->width = 0;
    this->height = 0;
}

// -------------------------------------------------------------------

ImgTexture::~ImgTexture() {
    this->free();
}

// --------------------------------------------------------------------

ImgTexture::free() {
    if(this->sdImgTexture != nullptr) {
        
        SDL_DestroyTexture(this->sdImgTexture);
        this->sdImgTexture = nullptr;
        
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
                        SDL_MapRGB(loadedSurface->format,
                                    0, 0xFF, 0xFF));

        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

        if(newTexture == nullptr) {
            std::cout << "Unable to create texture from '" << path.c_str() <<"'\n";
        } else {
            this->width = loadedSurface->w;
            this->height = loadedSurface->h;
        }

        SDL_FreeSurface(loadedSurface);
    }

    this->sdImgTexture = newTexture;
    return this->sdImgTexture != nullptr;
}

// ---------------------------------------------------------------------

void ImgTexture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
    SDL_SetTextureColorMod(this->sdImgTexture, red, green, blue);
}

// ---------------------------------------------------------------------

void ImgTexture::setBlendMode(SDL_BlendMode blending) {
    SDL_SetTextureBlendMode(this->sdImgTexture, blending);
}

// ---------------------------------------------------------------------

void ImgTexture::render(int posX, int posY, SDL_Rect* clip, double angle,
                         SDL_point* center, SDL_RendererFlip flip) 
{
    SDL_Rect renderQuad = {posX, posY, this->width, this->height};

    if(clip != nullptr) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx(gRenderer, this->sdImgTexture, clip, &renderQuad,
                    angle, center, flip);
}

// ---------------------------------------------------------------------



