#include "client/Boulder.h"
#include "client/SDLTextureLoader.h"

Boulder::Boulder() : StaticRenderizable() {
    w = 80;
    h = 75;
    img_x = 0;
    img_y = 0;
    real_resize = 2;
    SDLTextureLoader *loader = SDLTextureLoader::get_loader();
    std::string path = "client_src/img/boulder.png";
    this->texture = loader->get_texture(path);
}
