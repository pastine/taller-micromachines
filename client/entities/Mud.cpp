#include "client/Mud.h"
#include "client/SDLTextureLoader.h"

Mud::Mud() : StaticRenderizable() {
    w = 395;
    h = 143;
    img_x = 36;
    img_y = 40;
    resize_factor = 0.25;
    SDLTextureLoader *loader = SDLTextureLoader::get_loader();
    std::string path = "client/img/mud.png";
    this->texture = loader->get_texture(path);
}
