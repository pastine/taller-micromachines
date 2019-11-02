#ifndef TALLER_MICROMACHINES_ELEMENT_H
#define TALLER_MICROMACHINES_ELEMENT_H


#include <Box2D/Dynamics/b2World.h>

class Element {
public:
  static void get_element(b2World& world);

  virtual void destroy() = 0;

  virtual ~Element()= default;
};


#endif //TALLER_MICROMACHINES_ELEMENT_H
