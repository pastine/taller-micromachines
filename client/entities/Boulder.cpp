#include "client/Boulder.h"
#include "client/SDLTextureLoader.h"

Boulder::Boulder() : StaticRenderizable() {
    w = 550;
    h = 550;
    img_x = 0;
    img_y = 0;
    real_resize = 0.5;
    SDLTextureLoader *loader = SDLTextureLoader::get_loader();
    std::string path = "client/img/boulder.png";
    this->texture = loader->get_texture(path);
}
