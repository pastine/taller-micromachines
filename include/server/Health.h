#ifndef TALLER_MICROMACHINES_HEALTH_H
#define TALLER_MICROMACHINES_HEALTH_H

#include <Box2D/Box2D.h>
#include "server/Element.h"

class Health : public Element {
private:
    b2Body *m_body;

public:
    explicit Health(b2World &world, float x, float y);

    void start_contact() override;

    void end_contact() override;

    void destroy() override;

    b2Vec2 get_position() override;

    int get_entity_type() override;
};


#endif //TALLER_MICROMACHINES_HEALTH_H
