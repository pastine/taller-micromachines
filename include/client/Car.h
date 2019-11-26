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
public:
    Car();

    void render(SDL_Renderer *renderer, float x, float y,
                float angle = 0, int id = 0, float speed = 0) override;

    void increase_resize() override;

    void decrease_resize() override;

    void set_resize_factor(float resize) override;
};


#endif //TALLER_MICROMACHINES_CAR_H
