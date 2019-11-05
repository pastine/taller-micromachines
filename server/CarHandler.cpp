#include <iostream>
#include "server/CarHandler.h"
#define TORQUE 15

CarHandler::CarHandler(Car &car) : car(car) {
}

void CarHandler::move(MoveType move) {
  switch (move) {
      case UP :     std::cout << "up\n"; car.move_forward(); return;
    case DOWN :   std::cout << "down\n"; car.stop();         return;
    case LEFT :   std::cout << "left\n"; car.turn(TORQUE);   return;
    case RIGHT :  std::cout << "right\n"; car.turn(-TORQUE);  return;
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
