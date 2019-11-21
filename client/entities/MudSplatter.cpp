//
// Created by casimiro on 20/11/19.
//

#include <client/SDLTextureLoader.h>
#include "client/MudSplatter.h"

MudSplatter::MudSplatter() {
    w = 785;
    h = 441;
    img_x = 0;
    img_y = 0;
    resize_factor = 1;
    SDLTextureLoader *loader = SDLTextureLoader::get_loader();
    std::string path = "client/img/splatter.png";
    this->texture = loader->get_texture(path);
}


void MudSplatter::render(SDL_Renderer *renderer, float x, float y, int w_screen,
                         int h_screen) {
    Area src(img_x, img_y, w, h);
    Area dest(0, 0,
              w_screen * resize_factor * real_resize, h_screen * resize_factor * real_resize);
    this->texture->render(renderer, src, dest, 0);
}
