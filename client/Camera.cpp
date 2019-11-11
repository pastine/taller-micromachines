//
// Created by casimiro on 23/10/19.
//

#include <iostream>
#include "client/Camera.h"
#include "client/SDLWindow.h"
#include "client/SDLTextureLoader.h"

#define RENDER_BORDER_CM 200
#define PIXELS_TO_CM 1 // 29 * 5... dimentions of car


Camera::Camera() : window(SDLWindow(480, 840)){
    window.fill(0xFF,0xFF,0,0xFF);
    this->window.render();
    SDLTextureLoader::instance_loader(window.get_renderer());
}

void Camera::render_object(Renderizable& object, int abs_x, int abs_y, int angle, int id) {
    if (!this->_is_in_frame(object, abs_x, abs_y)) return;

    int x_distance_to_center_cms = abs_x - this->center_x_cms;
    int y_distance_to_center_cms = abs_y - this->center_y_cms;

    int x_distance_to_center_px = x_distance_to_center_cms * PIXELS_TO_CM;
    int y_distance_to_center_px = y_distance_to_center_cms * PIXELS_TO_CM;

    int relative_x_pos_px = this->center_x_px + x_distance_to_center_px;
    int relative_y_pos_px = this->center_y_px - y_distance_to_center_px;

    std::cout << "rendering object! at x: " << relative_x_pos_px;
    std::cout << " and y: " << relative_y_pos_px << "\n";
    std::cout << "center x: " << this->center_x_px << " center y: " << this->center_y_px;
    object.render(this->window.get_renderer(), relative_x_pos_px, relative_y_pos_px, angle, id);
}

void Camera::show_frame() {
    this->window.render();
}

void Camera::prepare_frame() {
    window.fill(0x0,0x84,0,0x42);
}

void Camera::set_center(int x, int y) {
    this->center_x_cms = x;
    this->center_y_cms = y;
    this->center_x_px = this->window.get_width() / 2;
    this->center_y_px = this->window.get_height() - (this->window.get_height() / 4);
}

bool Camera::_is_in_frame(Renderizable &object, int object_x_cms, int object_y_cms) {
    int w_width_cms = this->window.get_width() / PIXELS_TO_CM;
    int w_height_cms = this->window.get_height() / PIXELS_TO_CM;
    if (std::abs(this->center_x_cms - object_x_cms) > w_width_cms + RENDER_BORDER_CM) return false;
    return std::abs(this->center_y_cms - object_y_cms) <= w_height_cms + RENDER_BORDER_CM;
}

void Camera::render_car_lives(int lives) {
    CarLivesDrawer lives_drawer{};
    lives_drawer.draw_lives(lives, this->window.get_renderer());
}
