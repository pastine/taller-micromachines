#ifndef TALLER_MICROMACHINES_TRACK_H
#define TALLER_MICROMACHINES_TRACK_H
#include "Box2D/Box2D.h"
#include "Entity.h"

class Track : public Entity {
private:
  b2Body* track;
public:
  explicit Track(b2World& world);

	int get_entity_type() override;
};


#endif //TALLER_MICROMACHINES_TRACK_H
