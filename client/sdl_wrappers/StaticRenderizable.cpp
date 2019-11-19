#include "client/StaticRenderizable.h"


void StaticRenderizable::render(SDL_Renderer *renderer, int x, int y,
                                int angle, int id, bool moving) {
    Area src(img_x, img_y, w, h);
    Area dest(x, y, w * resize_factor * real_resize, h * resize_factor * real_resize);
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
