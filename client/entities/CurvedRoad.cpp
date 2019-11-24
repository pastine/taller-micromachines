#include <client/SDLTextureLoader.h>
#include "client/CurvedRoad.h"

CurvedRoad::CurvedRoad() {
    w = 688;
    h = 688;
    img_x = 0;
    img_y = 0;
    resize_factor = 1;
    SDLTextureLoader *loader = SDLTextureLoader::get_loader();
    std::string path = "client/img/curved-road.png";
    this->texture = loader->get_texture(path);
}
