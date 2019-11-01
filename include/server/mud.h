#ifndef TALLER_MICROMACHINES_MUD_H
#define TALLER_MICROMACHINES_MUD_H


#include <Box2D/Dynamics/b2World.h>

class Mud {
private:
  b2Body* m_body;
public:
  explicit Mud(b2World& world);
};


#endif //TALLER_MICROMACHINES_MUD_H
