#ifndef TALLER_MICROMACHINES_TRACK_H
#define TALLER_MICROMACHINES_TRACK_H

#include "Box2D/Box2D.h"
#include "Entity.h"
#include "common/Constants.h"
#include "Element.h"
#include "State.h"
#include <unordered_map>
#include <string>
#include <vector>

class Track : public Entity {
private:
    std::vector<Element *> static_elements;
	std::vector<Element *> elements;
public:
    explicit Track(b2World &world);

    int get_entity_type() override;

    JSON get_elements_state();

    std::vector<Element *> get_static_elements();

    b2Vec2 get_position() override;

    void delete_elements();

    void add_elements(State &state);
};


#endif //TALLER_MICROMACHINES_TRACK_H
