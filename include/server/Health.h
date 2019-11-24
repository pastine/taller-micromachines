#ifndef TALLER_MICROMACHINES_HEALTH_H
#define TALLER_MICROMACHINES_HEALTH_H

#include <Box2D/Box2D.h>
#include "common/Constants.h"
#include "Entity.h"


class Health : public Entity {
private:
	bool consumed;
	b2Fixture* fixture;
public:
	explicit Health(b2World &world, float x, float y);

	void start_contact() override;

	void end_contact() override;

	int get_entity_type() override;

	bool was_consumed();

	~Health() override;
};


#endif //TALLER_MICROMACHINES_HEALTH_H
