//
// Created by casimiro on 17/10/19.
//

#ifndef TALLER_MICROMACHINES_SDLTEXTURE_H
#define TALLER_MICROMACHINES_SDLTEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include "Area.h"


class SDLTexture {
public:
    SDLTexture(SDL_Texture* texture,
               SDL_Renderer* renderer,
               int width, int height);
    ~SDLTexture();
    void render(Area& src, Area& dest);
private:
    SDL_Texture* texture;
    SDL_Renderer* renderer;
    int width;
    int height;
};


#endif //TALLER_MICROMACHINES_SDLTEXTURE_H
