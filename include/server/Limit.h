#ifndef TALLER_MICROMACHINES_LIMIT_H
#define TALLER_MICROMACHINES_LIMIT_H


#include "Box2D/Box2D.h"
#include "common/Constants.h"
#include "Entity.h"

class Limit : public Entity {
public:
	explicit Limit(b2World &world);

	void start_contact() override;

	void end_contact() override;

	int get_entity_type() override;

	~Limit() override = default;
};

#endif //TALLER_MICROMACHINES_LIMIT_H
