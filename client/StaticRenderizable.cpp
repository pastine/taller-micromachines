//
// Created by casimiro on 25/10/19.
//

#include "client/StaticRenderizable.h"



void StaticRenderizable::render(SDL_Renderer* renderer, int x, int y, int angle) {
    Area src(img_x, img_y, w, h);
    Area dest(x, y, w* resize_factor, h * resize_factor);
    this->texture->render(renderer, src, dest);
}

StaticRenderizable::StaticRenderizable() : Renderizable() {}
