//
// Created by casimiro on 23/10/19.
//

#include "Mud.h"
#include "SDLTextureLoader.h"

Mud::Mud(SDL_Renderer *renderer) : Renderizable(renderer) {
    w = 550;
    h = 550;
    img_x = 0;
    img_y = 0;
    resize_factor = 0.5;
    SDLTextureLoader *loader =  SDLTextureLoader::get_loader();
    std::string path = "client/img/mud.png";
    this->texture = loader->get_texture(path);
}
