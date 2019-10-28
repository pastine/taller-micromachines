//
// Created by casimiro on 18/10/19.
//

#include <iostream>
#include "client/Car.h"
#include "client/SDLTextureLoader.h"

Car::Car() : Renderizable() {
    w = 29;
    h = 29;
    SDLTextureLoader *loader =  SDLTextureLoader::get_loader();
    std::string path = "client/img/cars_transparent.png";
    this->texture = loader->get_texture(path);
}


void Car::render(SDL_Renderer* renderer, int x, int y, int angle) {
    int _angle = angle % 180;
    Area& src = this->frames.resolve_frame(_angle);
    Area dest = Area(x, y, this->w*5, this->h*5);
    if (angle < 180)
        this->texture->render(renderer, src, dest);
    else
        this->texture->render_flipped(renderer, src, dest, SDL_FLIP_HORIZONTAL);
}


