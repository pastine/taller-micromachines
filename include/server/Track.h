#ifndef TALLER_MICROMACHINES_TRACK_H
#define TALLER_MICROMACHINES_TRACK_H

#include "Box2D/Box2D.h"
#include "Entity.h"
#include "common/Constants.h"
#include "State.h"
#include "Consumable.h"
#include "Entity.h"
#include "TrackStructure.h"
#include "TrackData.h"
#include <unordered_map>
#include <string>
#include <vector>
#include <set>

class Track : public Entity {
private:
	TrackStructure skeleton;
	std::vector<std::vector<float>> positions;
	std::vector<Entity*> static_elements;
	std::vector<Consumable*> elements;
	std::vector<Consumable*> to_remove;
	b2World* world;

public:
	explicit Track(b2World* world, char* file);

	int get_entity_type() override;

	void start_contact() override {};

	void end_contact() override {};

	JSON get_elements_state();

	TrackData get_static_data();

	std::vector<float> get_random_pos();

	std::vector<Consumable*> get_removable_elements();

	JSON get_straight_points();

	~Track() override;
};


#endif //TALLER_MICROMACHINES_TRACK_H
