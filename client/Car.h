//
// Created by casimiro on 18/10/19.
//

#ifndef TALLER_MICROMACHINES_CAR_H
#define TALLER_MICROMACHINES_CAR_H


#include <vector>
#include "Area.h"
#include "SDLTexture.h"
#include "CarFrameResolver.h"

class Car {
private:
    SDLTexture* car_texture;
    CarFrameResolver frames;
    int x;
    int y;
    int w;
    int h;
    int angle;
public:
    Car();
    void render(SDL_Renderer* renderer);
    void accelerate();
    void turn_left();
    void turn_right();
};


#endif //TALLER_MICROMACHINES_CAR_H
