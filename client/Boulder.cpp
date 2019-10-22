//
// Created by casimiro on 22/10/19.
//

#include "Boulder.h"
#include "SDLTextureLoader.h"

Boulder::Boulder(SDL_Renderer *renderer, int x, int y) {
    this->x = x;
    this->y = y;
    w = 550;
    h = 550;
    SDLTextureLoader *loader =  SDLTextureLoader::get_loader();
    std::string path = "client/img/boulder.png";
    this->boulder_texture = loader->get_texture(path);
}

void Boulder::render() {
    Area src(0, 0, w, h);
    Area dest(x, y, w* 0.25, h* 0.25);
    this->boulder_texture->render(src, dest);
}
