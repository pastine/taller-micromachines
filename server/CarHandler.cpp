#include <iostream>
#include <unordered_map>
#include "server/CarHandler.h"

CarHandler::CarHandler(Car* car) : car(car) {
}

void CarHandler::move(MoveType move) {
  switch (move) {
    case UP : car->move_forward(); return;
    case DOWN : car->stop(); return;
    case LEFT : car->turn_left(false); return;
    case RIGHT : car->turn_right(false);  return;
    case UPLEFT : car->turn_left(true);  return;
    case UPRIGHT : car->turn_right(true);  return;
    default: std::cout << "default\n"; return;
  }
}

CarHandler::~CarHandler() {
	delete(car);
}

std::unordered_map<std::string, std::string> CarHandler::get_position() {
	std::unordered_map<std::string, std::string> center;
	center.emplace(X, std::to_string(this->car->get_position().x));
	center.emplace(Y, std::to_string(this->car->get_position().y));
	return center;
}

void CarHandler::update_surface(){
  car->surface_effect();
}

float32 CarHandler::get_angle() {
  return car->get_angle();
}

std::unordered_map<std::string, std::string> CarHandler::get_user_state() {
	std::unordered_map<std::string, std::string> user;
	user.emplace("mud", car->get_mud_state());
	user.emplace("lives", car->get_lives());
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
