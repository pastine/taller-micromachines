#ifndef TALLER_MICROMACHINES_CAR_HANDLER_H
#define TALLER_MICROMACHINES_CAR_HANDLER_H

#include "car.h"

class CarHandler {
private:
  Car car;

public:
  explicit CarHandler(Car& car);

  void turn_left();

  void turn_right();

  void accelerate();

  void slow_down();

  ~CarHandler();
};


#endif //TALLER_MICROMACHINES_CAR_HANDLER_H
