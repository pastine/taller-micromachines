#ifndef TALLER_MICROMACHINES_TRACKDATA_H
#define TALLER_MICROMACHINES_TRACKDATA_H


#include <unordered_map>
#include <string>
#include <vector>
#include <Box2D/Common/b2Math.h>
#include <common/json.h>

class TrackData {
private:
    std::unordered_map<std::string, std::vector<b2Vec2>> static_elements;
    JSON track;
public:
    TrackData(std::unordered_map<std::string, std::vector<b2Vec2>>
              elements, JSON roads);

    std::unordered_map<std::string, std::vector<b2Vec2>> get_elements();

    JSON get_track();
};


#endif //TALLER_MICROMACHINES_TRACKDATA_H
