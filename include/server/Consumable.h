#ifndef TALLER_MICROMACHINES_CONSUMABLE_H
#define TALLER_MICROMACHINES_CONSUMABLE_H


#include <server/Entity.h>

class Consumable : public Entity {
public:
	bool consumed = false;

	virtual int get_entity_type() = 0;

	virtual bool was_consumed();
};


#endif //TALLER_MICROMACHINES_CONSUMABLE_H
