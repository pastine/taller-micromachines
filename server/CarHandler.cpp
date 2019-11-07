#include <iostream>
#include "server/CarHandler.h"
#define TORQUE 1500

CarHandler::CarHandler(Car &car) : car(car) {
}

void CarHandler::move(MoveType move) {
  switch (move) {
      case UP : car.move_forward(); return;
    case DOWN : car.stop();         return;
    case LEFT : return;
    case RIGHT :  car.turn_right();  return;
    default: std::cout << "default\n"; return;
  }
}

CarHandler::~CarHandler() {
}

b2Vec2 CarHandler::get_position() {
  return car.get_position();
}

bool CarHandler::is_colliding() {
  return car.is_colliding();
}

float32 CarHandler::get_angle() {
  return car.get_angle();
}
