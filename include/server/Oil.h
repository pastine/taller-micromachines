#ifndef TALLER_MICROMACHINES_OIL_H
#define TALLER_MICROMACHINES_OIL_H

#include "server/Entity.h"
#include "common/Constants.h"
#include <Box2D/Box2D.h>

class Oil : public Entity {
public:
    explicit Oil(b2World &world, float x, float y);

    void start_contact() override;

    void end_contact() override;

    int get_entity_type() override;

    ~Oil() override = default;
};

#endif //TALLER_MICROMACHINES_OIL_H
