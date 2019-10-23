//
// Created by casimiro on 23/10/19.
//

#include "Renderizable.h"


Renderizable::Renderizable() {}

void Renderizable::render(SDL_Renderer* renderer, int x, int y, int angle) {
    Area src(img_x, img_y, w, h);
    Area dest(x, y, w* resize_factor, h * resize_factor);
    this->texture->render(renderer, src, dest);
}
