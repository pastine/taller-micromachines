//
// Created by casimiro on 22/10/19.
//

#include "Boulder.h"
#include "SDLTextureLoader.h"

Boulder::Boulder() : Renderizable() {
    w = 550;
    h = 550;
    img_x = 0;
    img_y = 0;
    resize_factor = 0.25;
    SDLTextureLoader *loader =  SDLTextureLoader::get_loader();
    std::string path = "client/img/boulder.png";
    this->texture = loader->get_texture(path);
}
