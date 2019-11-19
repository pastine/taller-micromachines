#include <iostream>
#include <unordered_map>
#include <common/CommunicationConstants.h>
#include "server/CarHandler.h"

CarHandler::CarHandler(Car *car) : car(car) {
}

void CarHandler::move(MoveType move) {
    switch (move) {
        case UP :
            car->move_forward();
            return;
        case DOWN :
            car->stop();
            return;
        case LEFT :
            car->turn(true);
            return;
        case RIGHT :
            car->turn(false);
            return;
        case UPLEFT :
            car->move_forward();
            car->turn(true);
            return;
        case UPRIGHT :
            car->move_forward();
            car->turn(false);
            return;
        case DOWNLEFT :
            car->stop();
            car->turn(true);
            return;
        case DOWNRIGHT :
            car->stop();
            car->turn(false);
            return;
        default:
            std::cout << "default\n";
            return;
    }
}

CarHandler::~CarHandler() {
    delete (car);
}

std::unordered_map<std::string, std::string> CarHandler::get_position() {
    std::unordered_map<std::string, std::string> center;
    center.emplace(J_X, std::to_string(this->car->get_position().x));
    center.emplace(J_Y, std::to_string(this->car->get_position().y));
    return center;
}

void CarHandler::update_surface() {
    car->surface_effect();
}

float32 CarHandler::get_angle() {
    return car->get_angle();
}

std::unordered_map<std::string, std::string> CarHandler::get_user_state() {
    std::unordered_map<std::string, std::string> user;
    user.emplace(J_MUDS, car->get_mud_state());
    user.emplace(J_LIVES, car->get_lives());
    return user;
}

float CarHandler::get_x() {
    return car->get_position().x;
}

float CarHandler::get_y() {
    return car->get_position().y;
}

bool CarHandler::isMoving() {
    return car->isMoving();
}
