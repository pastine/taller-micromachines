#ifndef TALLER_MICROMACHINES_CAR_H
#define TALLER_MICROMACHINES_CAR_H


#include <vector>
#include "Area.h"
#include "SDLTexture.h"
#include "CarFrameResolver.h"
#include "Renderizable.h"
#include <tuple>

class Car : public Renderizable {
private:
    CarFrameResolver frames;
    int w;
    int h;
    SDLTexture *texture;
    std::vector<std::tuple<int, int, int>> colors;
    int resize_factor;
public:
    Car();

    void render(SDL_Renderer *renderer, int x, int y,
                int angle = 0, int id = 0, bool moving = false);
};


#endif //TALLER_MICROMACHINES_CAR_H
