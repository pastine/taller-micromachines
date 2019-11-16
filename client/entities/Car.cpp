//
// Created by casimiro on 18/10/19.
//

#include <iostream>
#include <fstream>
#include "client/Car.h"
#include "client/SDLTextureLoader.h"

Car::Car() : Renderizable() {
    w = 29;
    h = 29;
    SDLTextureLoader *loader =  SDLTextureLoader::get_loader();
    std::string path = "client/img/cars_transparent.png";
    this->texture = loader->get_texture(path);
    std::ifstream colors_file("client/img/car_colors.txt");
    std::string r, g, b;
    while (std::getline(colors_file, r, ',') &&
           std::getline(colors_file, g, ',') &&
           std::getline(colors_file, b, ',')) {
        colors.emplace_back(std::tuple<int,int,int>(std::stoi(r),std::stoi(g),std::stoi(b)));
    }
}


void Car::render(SDL_Renderer* renderer, int x, int y, int angle, int id, bool moving) {
    /*
     * The angle comes from 180 upto -180.
     * */
    std::tuple<int, int, int> index = colors[id % colors.size()];
    this->texture->change_color(index);
    int _angle = std::abs(angle);
    Area& src = this->frames.resolve_frame(_angle, moving);
    Area dest = Area(x, y, this->w*2, this->h*2);
    if (angle < 0) {
        this->texture->render(renderer, src, dest, 0);
    } else {
        this->texture->render_flipped(renderer, src, dest, SDL_FLIP_HORIZONTAL);
    }
}


