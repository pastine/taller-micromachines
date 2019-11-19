#ifndef TALLER_MICROMACHINES_BOOST_H
#define TALLER_MICROMACHINES_BOOST_H

#include "server/Element.h"
#include <Box2D/Box2D.h>

class Boost : public Element {
private:
    b2Body *m_body;

public:
    explicit Boost(b2World &world, float x, float y);

    void start_contact() override;

    void end_contact() override;

    void destroy() override;

    int get_entity_type() override;
};


#endif //TALLER_MICROMACHINES_BOOST_H
