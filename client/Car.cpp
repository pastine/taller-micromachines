//
// Created by casimiro on 18/10/19.
//

#include <iostream>
#include <tuple>
#include "client/Car.h"
#include "client/SDLTextureLoader.h"

std::vector<std::tuple<int,int,int>> colors{{240,163,255},{0,117,220},{153,63,0},{76,0,92},
                                            {25,25,25},{25,0,25},{0,92,49},{43,206,72},
                                            {255,204,153},{128,128,128},
                                            {148,255,181},{143,124,0},{157,204,0},
                                            {194,0,136},{0,51,128},
                                            {255,164,5},{255,168,187},{66,102,0},{255,0,16},
                                            {94,241,242},{0,153,143},
                                            {224,255,102},{116,10,255},
                                            {153,0,0},{255,255,128},{255,255,0},
                                            {255,80,5},
                                            {2,63,165},{125,135,185},{190,193,212},
                                            {214,188,192},{187,119,132},
                                            {142,6,59},{74,111,227},
                                            {133,149,225},{181,187,227},{230,175,185},
                                            {224,123,145},{211,63,106},{17,198,56},{141,213,147},
                                            {198,222,199},{234,211,198},{240,185,141},
                                            {239,151,8},
                                            {15,207,192},
                                            {156,222,214},{213,234,231},{243,225,235},
                                            {246,196,225},{247,156,212},
                                            {255,0,0}, {228,228,0}, {0,255,0},
                                            {0,255,255}, {176,176,255},
                                            {255,0,255}, {228,228,228},
                                            {176,0,0}, {186,186,0},
                                            {0,176,0}, {0,176,176}, {132,132,255},
                                            {176,0,176}, {186,186,186}, {135,0,0},
                                            {135,135,0}, {0,135,0}, {0,135,135},
                                            {73,73,255}, {135,0,135}, {135,135,135},
                                            {85,0,0}, {84,84,0}, {0,85,0},
                                            {0,85,85}, {0,0,255}, {85,0,85}, {84,84,84}
                                            };

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


