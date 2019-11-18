#ifndef TALLER_MICROMACHINES_TRACK_H
#define TALLER_MICROMACHINES_TRACK_H
#include "Box2D/Box2D.h"
#include "Entity.h"
#include "common/Constants.h"
#include "Element.h"
#include <unordered_map>
#include <string>
#include <vector>

class Track : public Entity {
private:
    b2Body *track;
    std::vector<Element*> static_elements;
    std::vector<Element*> elements;
public:
    explicit Track(b2World &world);

    int get_entity_type() override;

    std::unordered_map<std::string, std::string> get_elements_state();

    std::vector<Element*> get_static_elements();
    b2Vec2 get_position() override;
};



#endif //TALLER_MICROMACHINES_TRACK_H
