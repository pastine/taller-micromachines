#ifndef TALLER_MICROMACHINES_BOOST_H
#define TALLER_MICROMACHINES_BOOST_H


#include <Box2D/Box2D.h>
#include "Entity.h"

class Boost : public Entity {
private:
	bool consumed;
	b2Fixture* fixture;
public:
	explicit Boost(b2World &world, float x, float y);

	void start_contact() override;

	void end_contact() override;

	int get_entity_type() override;

	bool was_consumed();

	~Boost() override;
};


#endif //TALLER_MICROMACHINES_BOOST_H
