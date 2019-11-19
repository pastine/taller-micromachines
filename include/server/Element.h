#ifndef TALLER_MICROMACHINES_ELEMENT_H
#define TALLER_MICROMACHINES_ELEMENT_H

#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/b2Body.h>
#include <vector>
#include "server/Entity.h"

class Element : public Entity {
public:
	  static Element* get_element(b2World& world);

    virtual void destroy();

    virtual int get_entity_type() override = 0;

    virtual void start_contact() = 0;

    virtual void end_contact() = 0;

    virtual b2Vec2 get_position() override;

    virtual ~Element() {}

    static std::vector<float> get_random_pos();
};


#endif //TALLER_MICROMACHINES_ELEMENT_H
