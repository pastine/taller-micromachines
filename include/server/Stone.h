#ifndef TALLER_MICROMACHINES_STONE_H
#define TALLER_MICROMACHINES_STONE_H

#include <Box2D/Box2D.h>
#include "server/Element.h"

class Stone : public Element {
private:
	b2Body* m_body;
public:
	explicit Stone(b2World& world, float x, float y);

	void start_contact() override;

	void end_contact() override;

	void destroy() override;

	int get_entity_type() override;
    b2Vec2 get_position() override;
};


#endif //TALLER_MICROMACHINES_STONE_H
