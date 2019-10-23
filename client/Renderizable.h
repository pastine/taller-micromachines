//
// Created by casimiro on 23/10/19.
//

#ifndef TALLER_MICROMACHINES_RENDERIZABLE_H
#define TALLER_MICROMACHINES_RENDERIZABLE_H


#include <SDL2/SDL_system.h>
#include "SDLTexture.h"

class Renderizable {
protected:
    SDLTexture* texture;
    SDL_Renderer* renderer;
    int w;
    int h;
    size_t img_x;
    size_t img_y;
    float resize_factor = 1;
public:
    explicit Renderizable(SDL_Renderer* renderer);
    void render(int x, int y, int angle = 0);
};


#endif //TALLER_MICROMACHINES_RENDERIZABLE_H
