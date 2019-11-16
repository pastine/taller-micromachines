//
// Created by casimiro on 25/10/19.
//

#ifndef TALLER_MICROMACHINES_STATICRENDERIZABLE_H
#define TALLER_MICROMACHINES_STATICRENDERIZABLE_H


#include "Renderizable.h"

class StaticRenderizable : public Renderizable {
protected:
    SDLTexture* texture;
    int w;
    int h;
    size_t img_x;
    size_t img_y;
    float resize_factor = 1;
public:
    StaticRenderizable();
    void render(SDL_Renderer* renderer, int x, int y,
            int angle = 0, int id = 0, bool moving = false) override;
};


#endif //TALLER_MICROMACHINES_STATICRENDERIZABLE_H
