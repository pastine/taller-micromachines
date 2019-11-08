//
// Created by casimiro on 23/10/19.
//

#include <iostream>
#include "client/Camera.h"
#include "client/SDLWindow.h"
#include "client/SDLTextureLoader.h"


Camera::Camera() : window(SDLWindow(420, 840)){
    window.fill(0xFF,0xFF,0,0xFF);
    this->window.render();
    SDLTextureLoader::instance_loader(window.get_renderer());
}

void Camera::render_object(Renderizable& object, int abs_x, int abs_y, int angle, int id) {
    if (!this->_is_in_frame(object, abs_x, abs_y)) return;

    int x_distance_to_center_mts = abs_x - this->center_x_mts;
    int y_distance_to_center_mts = abs_y - this->center_y_mts;

    int x_distance_to_center_px = x_distance_to_center_mts * PIXELS_TO_M;
    int y_distance_to_center_px = y_distance_to_center_mts * PIXELS_TO_M;

    int relative_x_pos_px = this->center_x_px + x_distance_to_center_px;
    int relative_y_pos_px = this->center_y_px - y_distance_to_center_px;

    std::cout << "rendering object!\n";
    object.render(this->window.get_renderer(), relative_x_pos_px, relative_y_pos_px, angle, id);
}

void Camera::show_frame() {
    this->window.render();
}

void Camera::prepare_frame() {
    window.fill(0xFF,0xFF,0,0xFF);
}

void Camera::set_center(int x, int y) {
    this->center_x_mts = x;
    this->center_y_mts = y;
    this->center_x_px = this->window.get_width() / 2;
    this->center_y_px = this->window.get_height() - (this->window.get_height() / 4);
}

bool Camera::_is_in_frame(Renderizable &object, int object_x_mts, int object_y_mts) {
    int w_width_mts = this->window.get_width() / PIXELS_TO_M;
    int w_height_mts = this->window.get_height() / PIXELS_TO_M;
    if (std::abs(this->center_x_mts - object_x_mts) > w_width_mts) return false;
    return std::abs(this->center_y_mts - object_y_mts) <= w_height_mts;
}
