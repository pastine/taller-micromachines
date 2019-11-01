#include "server/car_handler.h"
#define TORQUE 15

CarHandler::CarHandler(Car &car) : car(car) {
}

void CarHandler::move(MoveType move) {
  switch (move) {
    case UP :     car.move_forward(); return;
    case DOWN :   car.stop();         return;
    case LEFT :   car.turn(TORQUE);   return;
    case RIGHT :  car.turn(-TORQUE);  return;
    default: return;
  }
}

CarHandler::~CarHandler() {
}

b2Vec2 CarHandler::get_position() {
  return car.get_position();
}

float32 CarHandler::get_angle() {
  return car.get_angle();
}
