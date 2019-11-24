#include "client/Boulder.h"
#include "client/SDLTextureLoader.h"

Boulder::Boulder() : StaticRenderizable() {
    w = 467;
    h = 436;
    img_x = 70;
    img_y = 43;
    real_resize = 0.25;
    SDLTextureLoader *loader = SDLTextureLoader::get_loader();
    std::string path = "client/img/boulder.png";
    this->texture = loader->get_texture(path);
}
