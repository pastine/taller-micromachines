#ifndef TALLER_MICROMACHINES_TRACK_H
#define TALLER_MICROMACHINES_TRACK_H

#include "Box2D/Box2D.h"
#include "Entity.h"
#include "common/Constants.h"
#include "Element.h"
#include "State.h"
#include "TrackStructure.h"
#include "TrackData.h"
#include <unordered_map>
#include <string>
#include <vector>

class Track : public Entity {
private:
	TrackStructure skeleton;
	std::vector<Element*> static_elements;
	std::vector<Element*> elements;
public:
    explicit Track(b2World& world, char* file);

    int get_entity_type() override;

    JSON get_elements_state();

    TrackData get_static_data();

    b2Vec2 get_position() override;

    void add_elements(State& state);

    ~Track();

	std::vector<float> get_random_pos();
};


#endif //TALLER_MICROMACHINES_TRACK_H
