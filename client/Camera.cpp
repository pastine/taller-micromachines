#include <iostream>
#include "client/Camera.h"
#include "client/SDLWindow.h"
#include "client/SDLTextureLoader.h"
#include "common/Constants.h"

#define RENDER_BORDER 100000
#define ZOOM 0.5


Camera::Camera() : window(SDLWindow(480, 840)) {
    window.fill(0xFF, 0xFF, 0, 0xFF);
    this->window.render();
    SDLTextureLoader::instance_loader(window.get_renderer());
}

void Camera::render_object(Renderizable &object, float abs_x, float abs_y,
                           float angle, int id, float speed) {
    if (!this->_is_in_frame(object, abs_x, abs_y)) return;

    float x_distance_to_center_cms = abs_x - this->center_x_cms;
    float y_distance_to_center_cms = abs_y - this->center_y_cms;

    float x_distance_to_center_px = x_distance_to_center_cms * PIXELS_TO_CM;
    float y_distance_to_center_px = y_distance_to_center_cms * PIXELS_TO_CM;

    float relative_x_pos_px = this->center_x_px + x_distance_to_center_px;
    float relative_y_pos_px = this->center_y_px - y_distance_to_center_px;

    object.set_resize_factor(ZOOM);
    object.render(this->window.get_renderer(), relative_x_pos_px * ZOOM, relative_y_pos_px * ZOOM,
                  angle, id, speed);
}

void Camera::show_frame() {
    this->window.render();
}

void Camera::prepare_frame() {
    window.fill(0x0, 0x84, 0, 0x42);
}

void Camera::set_center(float x, float y) {
    this->center_x_cms = x;
    this->center_y_cms = y;
    this->center_x_px = this->window.get_width() / 2;
    this->center_y_px = this->window.get_height() - (this->window.get_height() / 3);
}

bool Camera::_is_in_frame(Renderizable &object, float object_x_cms, float object_y_cms) {
    float w_width_cms = this->window.get_width() / PIXELS_TO_CM;
    float w_height_cms = this->window.get_height() / PIXELS_TO_CM;
    if (std::abs(this->center_x_cms - object_x_cms) > w_width_cms + RENDER_BORDER) return false;
    return std::abs(this->center_y_cms - object_y_cms) <= w_height_cms + RENDER_BORDER;
}

void Camera::render_car_lives(int lives) {
    CarLivesDrawer lives_drawer;
    lives_drawer.draw_lives(lives, this->window.get_renderer());
}

void Camera::render_text() {
    this->text_creator.render_text("Hola mundo", this->window.get_renderer(), 10, 50);
}

void Camera::render_splatter() {
    MudSplatter splatter;
    splatter.render(this->window.get_renderer(),
            0,0, this->window.get_width(), this->window.get_height());
}
