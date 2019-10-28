//
// Created by casimiro on 18/10/19.
//

#ifndef TALLER_MICROMACHINES_CAR_H
#define TALLER_MICROMACHINES_CAR_H


#include <vector>
#include "Area.h"
#include "SDLTexture.h"
#include "CarFrameResolver.h"
#include "Renderizable.h"

class Car : public Renderizable {
private:
    CarFrameResolver frames;
    int w;
    int h;
    SDLTexture* texture;
public:
    Car();
    void render(SDL_Renderer* renderer, int x, int y, int angle = 0);
};


#endif //TALLER_MICROMACHINES_CAR_H
