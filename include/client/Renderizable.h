//
// Created by casimiro on 23/10/19.
//

#ifndef TALLER_MICROMACHINES_RENDERIZABLE_H
#define TALLER_MICROMACHINES_RENDERIZABLE_H


#include <SDL2/SDL_system.h>
#include "SDLTexture.h"

class Renderizable {
public:
    virtual void render(SDL_Renderer *renderer, int x, int y,
                        int angle = 0, int id = 0, bool moving = false) = 0;
};


#endif //TALLER_MICROMACHINES_RENDERIZABLE_H
