//
// Created by casimiro on 22/10/19.
//

#ifndef TALLER_MICROMACHINES_BOULDER_H
#define TALLER_MICROMACHINES_BOULDER_H


#include "SDLTexture.h"

class Boulder {
private:
    SDL_Renderer* renderer;
    SDLTexture* boulder_texture;
    int x;
    int y;
    int w;
    int h;
public:
    Boulder(SDL_Renderer* renderer, int x, int y);
    void render();
};


#endif //TALLER_MICROMACHINES_BOULDER_H
