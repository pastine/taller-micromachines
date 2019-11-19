#include <iostream>
#include <fstream>
#include "client/Car.h"
#include "client/SDLTextureLoader.h"
#include "common/Constants.h"

Car::Car() : Renderizable() {
    w = 29;
    h = 29;
    SDLTextureLoader *loader = SDLTextureLoader::get_loader();
    std::string path = "client/img/cars_transparent.png";
    this->texture = loader->get_texture(path);
    std::ifstream colors_file("client/img/car_colors.txt");
    std::string r, g, b;
    while (std::getline(colors_file, r, ',') &&
           std::getline(colors_file, g, ',') &&
           std::getline(colors_file, b, ',')) {
        colors.emplace_back(std::tuple<int, int, int>(std::stoi(r), std::stoi(g), std::stoi(b)));
    }
}


void Car::render(SDL_Renderer *renderer, int x, int y, int angle, int id, bool moving) {
    /*
     * The angle comes from 180 upto -180.
     * */
    std::tuple<int, int, int> index = colors[id % colors.size()];
    this->texture->change_color(index);
    int _angle = std::abs(angle);
    Area &src = this->frames.resolve_frame(_angle, moving);
    Area dest = Area(x, y, this->w * resize_factor * CAR_RESIZE_FACTOR,
                          this->h * resize_factor * CAR_RESIZE_FACTOR);
    if (angle < 0) {
        this->texture->render(renderer, src, dest, 0);
    } else {
        this->texture->render_flipped(renderer, src, dest, SDL_FLIP_HORIZONTAL);
    }
}

void Car::increase_resize() {
    this->resize_factor += 0.1;
}


void Car::decrease_resize() {
    if (this->resize_factor == 0) return;
    this->resize_factor -= 0.1;
}

void Car::set_resize_factor(float resize) {
    if (resize < 0) return;
    this->resize_factor = resize;
}
