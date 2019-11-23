#ifndef TALLER_MICROMACHINES_MUD_H
#define TALLER_MICROMACHINES_MUD_H

#include <Box2D/Box2D.h>
#include "common/Constants.h"
#include "Entity.h"

class Mud : public Entity {
public:
	explicit Mud(b2World &world, float x, float y);

	int get_entity_type() override;

	void start_contact() override;

	void end_contact() override;

	~Mud() override = default;
};


#endif //TALLER_MICROMACHINES_MUD_H
