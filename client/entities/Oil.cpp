#include "client/Oil.h"
#include "client/SDLTextureLoader.h"

Oil::Oil() : StaticRenderizable() {
    w = 395;
    h = 143;
    img_x = 36;
    img_y = 40;
    resize_factor = 0.25;
    SDLTextureLoader *loader = SDLTextureLoader::get_loader();
    std::string path = "client/img/oil.png";
    this->texture = loader->get_texture(path);
}
