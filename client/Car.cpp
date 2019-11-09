//
// Created by casimiro on 18/10/19.
//

#include <iostream>
#include <tuple>
#include "client/Car.h"
#include "client/SDLTextureLoader.h"

std::vector<std::tuple<int,int,int>> colors{{255, 255, 255}, {255, 0, 0},
                                            {255, 165, 0}, {0, 165, 255},
                                            {165, 255, 0}, {165, 0, 255}};

Car::Car() : Renderizable() {
    w = 29;
    h = 29;
    SDLTextureLoader *loader =  SDLTextureLoader::get_loader();
    std::string path = "client/img/cars_transparent.png";
    this->texture = loader->get_texture(path);
}


void Car::render(SDL_Renderer* renderer, int x, int y, int angle, int id) {
    /*
     * The angle comes from 180 upto -180.
     * */
    std::tuple<int, int, int> index = colors[id % colors.size()];
    this->texture->change_color(index);
    int _angle = std::abs(angle);
    Area& src = this->frames.resolve_frame(_angle);
    Area dest = Area(x, y, this->w*2, this->h*2);
    if (angle < 0) {
        this->texture->render(renderer, src, dest, 0);
    } else {
        this->texture->render_flipped(renderer, src, dest, SDL_FLIP_HORIZONTAL);
    }
}


