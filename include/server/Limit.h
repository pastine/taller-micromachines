#ifndef TALLER_MICROMACHINES_LIMIT_H
#define TALLER_MICROMACHINES_LIMIT_H


#include "Box2D/Box2D.h"
#include "common/Constants.h"
#include "Element.h"

class Limit : public Element {
private:
    b2Body *limit;
public:
    explicit Limit(b2World &world);

    void start_contact() override;

    void end_contact() override;

    b2Vec2 get_position() override;

    int get_entity_type() override;

    void destroy() override;
};

#endif //TALLER_MICROMACHINES_LIMIT_H
