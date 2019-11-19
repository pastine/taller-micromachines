#include <client/SDLTextureLoader.h>
#include "client/CurvedRoad.h"

CurvedRoad::CurvedRoad() {
    w = 550;
    h = 550;
    img_x = 0;
    img_y = 0;
    resize_factor = 0.5;
    SDLTextureLoader *loader = SDLTextureLoader::get_loader();
    std::string path = "client/img/curved-road.png";
    this->texture = loader->get_texture(path);
}
