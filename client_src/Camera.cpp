#include <iostream>
#include <sstream>
#include "client/Camera.h"
#include "client/SDLWindow.h"
#include "client/SDLTextureLoader.h"
#include "common/Constants.h"

#define RENDER_BORDER 100000
#define ZOOM 0.4 // the less the furthest


Camera::Camera() : window(SDLWindow(480, 840)) {
    SDLTextureLoader::instance_loader(window.get_renderer());
}

void Camera::render_object(Renderizable &object, float abs_x, float abs_y,
                           float angle, int id, float speed) {
    if (!this->_is_in_frame(object, abs_x, abs_y)) return;

    float x_distance_to_center_cms = abs_x - this->center_x_cms;
    float y_distance_to_center_cms = abs_y - this->center_y_cms;

    float x_distance_to_center_px = x_distance_to_center_cms * TO_PX;
    float y_distance_to_center_px = y_distance_to_center_cms * TO_PX;

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
    this->center_y_px /= ZOOM;
    this->center_x_px /= ZOOM;
}

bool Camera::_is_in_frame(Renderizable &object, float object_x_cms, float object_y_cms) {
    float w_width_cms = this->window.get_width() / TO_PX;
    float w_height_cms = this->window.get_height() / TO_PX;
    if (std::abs(this->center_x_cms - object_x_cms) > w_width_cms + RENDER_BORDER) return false;
    return std::abs(this->center_y_cms - object_y_cms) <= w_height_cms + RENDER_BORDER;
}

void Camera::render_car_lives(int lives) {
    CarLivesDrawer lives_drawer;
    lives_drawer.draw_lives(lives, this->window.get_renderer());
}

void Camera::render_splatter() {
    MudSplatter splatter;
    splatter.render(this->window.get_renderer(),
                    0, 0, this->window.get_width(), this->window.get_height());
}

void Camera::render_name(std::string name) {
    int padding = 25;
    this->text_creator.render_text(name, this->window.get_renderer(), padding, 80);
}

Camera::~Camera() {
    SDLTextureLoader *loader = SDLTextureLoader::get_loader();
    loader->free_textures();
}

void Camera::render_podium(size_t position) {
    if (position <= 3) {
        this->text_creator.render_text("Congratulations" + std::string(position, '!'),
                                       this->window.get_renderer(), this->window.get_width() - 350, 40);
    }
    std::ostringstream str;
    str << "Final Position: " << position;
    this->text_creator.render_text(str.str(), this->window.get_renderer(),
                                   this->window.get_width() - 350, 70);
}

void Camera::render_lapcount(int lapcount, int total_laps) {
    std::ostringstream str;
    str << lapcount << "/" << total_laps << " laps";
    this->text_creator.render_text(str.str(),
                                   this->window.get_renderer(), this->window.get_width() - 150, 40);
}
