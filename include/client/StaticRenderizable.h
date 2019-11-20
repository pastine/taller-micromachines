#ifndef TALLER_MICROMACHINES_STATICRENDERIZABLE_H
#define TALLER_MICROMACHINES_STATICRENDERIZABLE_H


#include "Renderizable.h"

class StaticRenderizable : public Renderizable {
protected:
    SDLTexture *texture;
    int w;
    int h;
    size_t img_x;
    size_t img_y;
    float resize_factor = 1;
    float real_resize = 1;
public:
    StaticRenderizable();

    void render(SDL_Renderer *renderer, float x, float y,
                float angle = 0, int id = 0, float speed = 0) override;

    explicit StaticRenderizable(SDLTexture *texture);

    void increase_resize() override;
    void decrease_resize() override;
    void set_resize_factor(float resize) override;
};


#endif //TALLER_MICROMACHINES_STATICRENDERIZABLE_H
