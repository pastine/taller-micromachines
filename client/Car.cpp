//
// Created by casimiro on 18/10/19.
//

#include <iostream>
#include "Car.h"
#include "SDLTextureLoader.h"

Car::Car(SDL_Renderer *renderer) : renderer(renderer) {
    x = 100;
    y = 100;
    w = 29;
    h = 29;
    SDLTextureLoader *loader =  SDLTextureLoader::get_loader();
    std::string path = "client/img/cars_transparent.png";
    this->car_texture = loader->get_texture(path);
}

void Car::turn_right() {
    angle += 15;
    if (angle == 360) angle = 0;

}

void Car::turn_left() {
    angle -= 15;
    if (angle == -15) angle = 345;
}

void Car::accelerate() {
    return;
}

void Car::render() {
    int _angle = this->angle % 180;
    Area& src = this->frames.resolve_frame(_angle);
    Area dest = Area(this->x, this->y, this->w*5, this->h*5);
    if (this->angle < 180)
        this->car_texture->render(src, dest);
    else
        this->car_texture->render_flipped(src, dest, SDL_FLIP_HORIZONTAL);
}


