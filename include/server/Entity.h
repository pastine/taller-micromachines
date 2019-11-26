#ifndef TALLER_MICROMACHINES_ENTITY_H
#define TALLER_MICROMACHINES_ENTITY_H

#include <Box2D/Box2D.h>

class Entity {
public:
    b2Body *m_body;

    virtual int get_entity_type() = 0;

    virtual void start_contact() {}

    virtual void end_contact() {}

    virtual b2Vec2 get_position();

    virtual ~Entity() {}
};

#endif //TALLER_MICROMACHINES_ENTITY_H
