#include <iostream>
#include <unordered_map>
#include "server/CarHandler.h"
#include "common/Constants.h"
#define TORQUE 1500

CarHandler::CarHandler(Car &car) : car(car) {
}

void CarHandler::move(MoveType move) {
  switch (move) {
    case UP : car.move_forward(); return;
    case DOWN : car.stop();         return;
    case LEFT : car.turn_left(); return;
    case RIGHT :  car.turn_right();  return;
    default: std::cout << "default\n"; return;
  }
}

CarHandler::~CarHandler() {
}

std::unordered_map<std::string, std::string> CarHandler::get_position() {
	std::unordered_map<std::string, std::string> center;
	center.emplace(X, std::to_string(this->car.get_position().x));
	center.emplace(Y, std::to_string(this->car.get_position().y));
	return center;
}

void CarHandler::update_surface(){
  car.surface_effect();
}

float32 CarHandler::get_angle() {
  return car.get_angle();
}

std::unordered_map<std::string, std::string> CarHandler::get_element_state() {
	std::unordered_map<std::string, std::string> elements;
	elements.emplace("mud", car.get_mud_state());
	elements.emplace("lives", car.get_lives());
	return elements;
}

float CarHandler::get_x() {
	return car.get_position().x;
}

float CarHandler::get_y() {
	return car.get_position().y;
}
