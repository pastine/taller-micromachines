#ifndef TALLER_MICROMACHINES_CARHANDLER_H
#define TALLER_MICROMACHINES_CARHANDLER_H

#include <utility>
#include <common/MoveType.h>
#include "Car.h"

class CarHandler {
private:
  Car car;

public:
  explicit CarHandler(Car& car);

  void move(MoveType move);

  b2Vec2 get_position();

  float32 get_angle();

  void update_surface();

  ~CarHandler();
};


#endif //TALLER_MICROMACHINES_CARHANDLER_H
