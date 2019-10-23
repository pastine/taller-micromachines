//
// Created by casimiro on 23/10/19.
//

#include "Camara.h"
#include "SDLWindow.h"
#include "SDLTextureLoader.h"


Camara::Camara() : window(SDLWindow(420, 840)){
    window.fill(0xFF,0xFF,0,0xFF);
    this->window.render();
    SDLTextureLoader::instance_loader(window.get_renderer());
}

void Camara::render_object(Renderizable object, int abs_x, int abs_y, int angle) {
    object.render(this->window.get_renderer(), abs_x, abs_y);
}

void Camara::show_frame() {
    this->window.render();
}
