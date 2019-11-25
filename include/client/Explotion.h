#ifndef TALLER_MICROMACHINES_EXPLOTION_H
#define TALLER_MICROMACHINES_EXPLOTION_H


#include <client/Renderizable.h>
#include "client/ExplotionFrameResolver.h"

class Explotion : public Renderizable {
private:
    int w;
    int h;
    SDLTexture *texture;
    ExplotionFrameResolver frame_resolver;
public:
    Explotion();

    void render(SDL_Renderer *renderer, float x, float y,
                float angle = 0, int id = 0, float speed = 0) override;

    bool is_done();

    void increase_resize() override;
    void decrease_resize() override;
    void set_resize_factor(float resize) override;
};


#endif //TALLER_MICROMACHINES_EXPLOTION_H
