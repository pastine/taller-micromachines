#include <client/SDLTextureLoader.h>
#include <iostream>
#include "client/Explotion.h"
#include "common/Constants.h"


Explotion::Explotion() {
    w = 253;
    h = 204;
    SDLTextureLoader *loader = SDLTextureLoader::get_loader();
    std::string path = "client/img/explotion.png";
    this->texture = loader->get_texture(path);
}

void Explotion::increase_resize() {
    this->resize_factor += 0.1;
}


void Explotion::decrease_resize() {
    if (this->resize_factor == 0) return;
    this->resize_factor -= 0.1;
}

void Explotion::set_resize_factor(float resize) {
    if (resize < 0) return;
    this->resize_factor = resize;
}

void
Explotion::render(SDL_Renderer *renderer, float x, float y, float angle, int id,
                  float speed) {
    if (this->frame_resolver.is_done()) return;

    float x_topleft= x - (w * resize_factor / 2);
    float y_topleft = y - (h * resize_factor / 2);

    Area src = this->frame_resolver.resolve_frame();
    Area dest(x_topleft, y_topleft, w * resize_factor, h * resize_factor);

    this->texture->render(renderer, src, dest, angle);
}

bool Explotion::is_done() {
    return this->frame_resolver.is_done();
}
