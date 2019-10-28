#include "car_handler.h"
#define TORQUE 15

CarHandler::CarHandler(Car &car) : car(car) {
}

void CarHandler::turn_left() {
  car.turn(TORQUE);
}

void CarHandler::turn_right() {
  car.turn(-TORQUE);
}

void CarHandler::accelerate() {

}

void CarHandler::slow_down() {

}

CarHandler::~CarHandler() {

}

