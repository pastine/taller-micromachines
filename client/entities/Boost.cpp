//
// Created by casimiro on 10/11/19.
//

#include <client/SDLTextureLoader.h>
#include "client/Boost.h"

Boost::Boost() {
    w = 50;
    h = 50;
    img_x = 0;
    img_y = 0;
    resize_factor = 3;
    SDLTextureLoader *loader =  SDLTextureLoader::get_loader();
    std::string path = "client/img/boost.png";
    this->texture = loader->get_texture(path);
}
