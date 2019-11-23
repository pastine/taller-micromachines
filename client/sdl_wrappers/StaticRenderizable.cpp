#include "client/StaticRenderizable.h"
#include <math.h>

void StaticRenderizable::render(SDL_Renderer *renderer, float x_center, float y_center,
                                float angle, int id, float speed) {
    Area src(img_x, img_y, w, h);

    float x_topleft = x_center - ((w * resize_factor / 2));

    float y_topleft = y_center - ((h * resize_factor / 2));

    Area dest(x_topleft, y_topleft,
            w * resize_factor * real_resize, h * resize_factor * real_resize);
    this->texture->render(renderer, src, dest, angle);
}

StaticRenderizable::StaticRenderizable() : Renderizable() {}

StaticRenderizable::StaticRenderizable(SDLTexture *texture) : Renderizable(),
                                                              texture(texture) {}

void StaticRenderizable::increase_resize() {
    this->resize_factor += 0.1;
}

void StaticRenderizable::decrease_resize() {
    if (this->resize_factor == 0) return;
    this->resize_factor -= 0.1;
}

void StaticRenderizable::set_resize_factor(float resize) {
    if (resize < 0) return;
    this->resize_factor = resize;
}
