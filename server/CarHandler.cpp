#include <iostream>
#include <unordered_map>
#include <common/CommunicationConstants.h>
#include "server/CarHandler.h"

CarHandler::CarHandler(Car *car) : car(car) {
}

void CarHandler::move(MoveType move) {
    switch (move) {
        case UP :
            car->move_straight(true);
            return;
        case DOWN :
            car->move_straight(false);
            return;
        case LEFT :
            car->turn(true);
            return;
        case RIGHT :
            car->turn(false);
            return;
        case UPLEFT :
            car->move_straight(true);
            car->turn(true);
            return;
        case UPRIGHT :
            car->move_straight(true);
            car->turn(false);
            return;
        case DOWNLEFT :
            car->move_straight(false);
            car->turn(false);
            return;
        case DOWNRIGHT :
            car->move_straight(false);
            car->turn(true);
            return;
        default:
            std::cout << "default\n";
            return;
    }
}

CarHandler::~CarHandler() {
    delete (car);
}

std::tuple<float, float, float> CarHandler::get_position() {
    return {car->get_position().x, car->get_position().y, car->get_angle()};
}

void CarHandler::update_surface() {
    car->surface_effect();
}

std::unordered_map<std::string, std::string> CarHandler::get_user_state() {
    std::unordered_map<std::string, std::string> user;
    user.emplace(J_MUDS, car->get_mud_state());
    user.emplace(J_LIVES, car->get_lives());
    return user;
}

bool CarHandler::isMoving() {
    return car->isMoving();
}
