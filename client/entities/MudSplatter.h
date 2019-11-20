//
// Created by casimiro on 20/11/19.
//

#ifndef TALLER_MICROMACHINES_MUDSPLATTER_H
#define TALLER_MICROMACHINES_MUDSPLATTER_H


#include <client/StaticRenderizable.h>

class MudSplatter : public StaticRenderizable {
public:
    MudSplatter();
    void render(SDL_Renderer *renderer, float x, float y, int w_screen, int h_screen);
};


#endif //TALLER_MICROMACHINES_MUDSPLATTER_H
