//
// Created by casimiro on 23/10/19.
//

#include "client/Camera.h"
#include "client/SDLWindow.h"
#include "client/SDLTextureLoader.h"


Camera::Camera() : window(SDLWindow(420, 840)){
    window.fill(0xFF,0xFF,0,0xFF);
    this->window.render();
    SDLTextureLoader::instance_loader(window.get_renderer());
}

void Camera::render_object(Renderizable& object, int abs_x, int abs_y, int angle) {
    object.render(this->window.get_renderer(), abs_x, abs_y, angle);
}

void Camera::show_frame() {
    this->window.render();
}

void Camera::prepare_frame() {
    window.fill(0xFF,0xFF,0,0xFF);
}
