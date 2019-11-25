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
            return;
    }
}

std::tuple<float, float, float> CarHandler::get_position() {
    return {car->get_position().x, car->get_position().y, car->get_angle()};
}

std::unordered_map<std::string, int> CarHandler::get_lives() {
    std::unordered_map<std::string, int> lives;
    lives.emplace(J_LIVES, car->get_lives());
    return lives;
}

std::unordered_map<std::string, bool> CarHandler::get_crash_state() {
	std::unordered_map<std::string, bool> crash;
	crash.emplace(J_CRASH, car->get_crash_state());
	return crash;
}

std::unordered_map<std::string, bool> CarHandler::get_mud_state() {
    std::unordered_map<std::string, bool> mud;
    mud.emplace(J_MUD, car->get_mud_state());
    return mud;
}

float CarHandler::get_speed() {
    return car->get_speed();
}

CarHandler::~CarHandler() {
	delete (car);
}
