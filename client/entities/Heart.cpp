#include <client/SDLTextureLoader.h>
#include "client/Heart.h"

Heart::Heart() {
    w = 50;
    h = 50;
    img_x = 0;
    img_y = 0;
    real_resize = 5;
    SDLTextureLoader *loader = SDLTextureLoader::get_loader();
    std::string path = "client/img/heart.png";
    this->texture = loader->get_texture(path);
}
