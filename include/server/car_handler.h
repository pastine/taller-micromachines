#ifndef TALLER_MICROMACHINES_CAR_HANDLER_H
#define TALLER_MICROMACHINES_CAR_HANDLER_H

#include <utility>
#include <common/MoveType.h>
#include "car.h"

class CarHandler {
private:
  Car car;

public:
  explicit CarHandler(Car& car);

  void move(MoveType move);

  b2Vec2 get_position();

  float32 get_angle();

  ~CarHandler();
};


#endif //TALLER_MICROMACHINES_CAR_HANDLER_H
