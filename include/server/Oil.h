#ifndef TALLER_MICROMACHINES_OIL_H
#define TALLER_MICROMACHINES_OIL_H

#include "server/Element.h"
#include "common/Constants.h"
#include <Box2D/Box2D.h>

class Oil : public Element {
private:
	b2Body* m_body;
public:
	explicit Oil(b2World& world, float x, float y);

	void start_contact() override;

	void end_contact() override;

	void destroy() override;

	int get_entity_type() override;
    b2Vec2 get_position() override;
};

#endif //TALLER_MICROMACHINES_OIL_H
