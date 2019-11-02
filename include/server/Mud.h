#ifndef TALLER_MICROMACHINES_MUD_H
#define TALLER_MICROMACHINES_MUD_H

#include <Box2D/Dynamics/b2World.h>
#include "Element.h"
#include "ContactListener.h"

class Mud {
private:
  b2Body* m_body;
  int contacts;
  ContactListener contact;

public:
  explicit Mud(b2World& world);

  void start_contact();

  void end_contact();

  void destroy();

  ~Mud(){}
};


#endif //TALLER_MICROMACHINES_MUD_H
