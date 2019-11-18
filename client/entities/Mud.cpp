//
// Created by casimiro on 23/10/19.
//

#include "client/Mud.h"
#include "client/SDLTextureLoader.h"

Mud::Mud() : StaticRenderizable() {
    w = 550;
    h = 550;
    img_x = 0;
    img_y = 0;
    resize_factor = 0.25;
    SDLTextureLoader *loader =  SDLTextureLoader::get_loader();
    std::string path = "client/img/mud.png";
    this->texture = loader->get_texture(path);
}
