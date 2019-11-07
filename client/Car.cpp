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
    /*
     * The angle comes from 180 upto -180.
     * */
    int _angle = std::abs(angle);
    Area& src = this->frames.resolve_frame(_angle);
    Area dest = Area(x, y, this->w*2, this->h*2);
    if (angle < 180)
        this->texture->render(renderer, src, dest);
    else
        this->texture->render_flipped(renderer, src, dest, SDL_FLIP_HORIZONTAL);
}


