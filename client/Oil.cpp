//
// Created by casimiro on 23/10/19.
//

#include "Oil.h"
#include "SDLTextureLoader.h"

Oil::Oil() : StaticRenderizable() {
    w = 550;
    h = 550;
    img_x = 0;
    img_y = 0;
    resize_factor = 0.5;
    SDLTextureLoader *loader =  SDLTextureLoader::get_loader();
    std::string path = "client/img/oil.png";
    this->texture = loader->get_texture(path);
}
