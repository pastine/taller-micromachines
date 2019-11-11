#ifndef TALLER_MICROMACHINES_ELEMENT_H
#define TALLER_MICROMACHINES_ELEMENT_H

#include <Box2D/Dynamics/b2World.h>
#include "server/Entity.h"

class Element : public Entity {
public:
  static Element* get_element(b2World& world);

  virtual void destroy() = 0;

  virtual int get_entity_type() = 0;

  virtual void start_contact() = 0;

	virtual void end_contact() = 0;

	virtual ~Element() {}
};



#endif //TALLER_MICROMACHINES_ELEMENT_H
