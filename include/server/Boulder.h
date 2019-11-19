#ifndef TALLER_MICROMACHINES_BOULDER_H
#define TALLER_MICROMACHINES_BOULDER_H

#include <Box2D/Box2D.h>
#include "server/Element.h"

class Boulder : public Element {
public:
    explicit Boulder(b2World &world, float x, float y);

    void start_contact() override;

    void end_contact() override;

    int get_entity_type() override;
};


#endif //TALLER_MICROMACHINES_BOULDER_H
