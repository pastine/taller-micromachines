#include <SDL2/SDL_render.h>
#include "client/SwsContext.h"
#include "common/Constants.h"

SwsContext::SwsContext(ProtectedQueue<std::vector<char>> &producedFrames) :
// Este buffer tiene el tamaño de la sección de SDL que quiero leer, multiplico
// x3 por la cantidad de bytes (8R,8G,8B)
// A sws parece que no le gusta este tamaño
        dataBuffer(CAM_WIDTH * CAM_HEIGHT * 3),
        producedFrames(producedFrames) {}

void SwsContext::write(SDLWindow &window) {
    // Obtengo los bytes de la textura en el buffer
    SDL_Renderer *r = window.get_renderer();
    char *d = dataBuffer.data();
    SDL_RenderReadPixels(r, NULL, SDL_PIXELFORMAT_RGB24, d, CAM_WIDTH * 3);
    //operacion lenta que pasó a otro thread:
    producedFrames.push(dataBuffer);
}
