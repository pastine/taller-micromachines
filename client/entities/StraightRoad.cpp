#include <client/SDLTextureLoader.h>
#include "client/StraightRoad.h"

StraightRoad::StraightRoad() {
    w = 550;
    h = 690;
    img_x = 0;
    img_y = 0;
    resize_factor = 1;
    SDLTextureLoader *loader = SDLTextureLoader::get_loader();
    std::string path = "client/img/straight-road.png";
    this->texture = loader->get_texture(path);
}
