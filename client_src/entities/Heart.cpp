#include <client/SDLTextureLoader.h>
#include "client/Heart.h"

Heart::Heart() {
    w = 9;
    h = 8;
    img_x = 0;
    img_y = 0;
    real_resize = 5;
    SDLTextureLoader *loader = SDLTextureLoader::get_loader();
    std::string path = "client_src/img/heart.png";
    this->texture = loader->get_texture(path);
}
