#ifndef TALLER_MICROMACHINES_TRACKSERIALIZER_H
#define TALLER_MICROMACHINES_TRACKSERIALIZER_H


#include <string>
#include <common/Serializer.h>
#include <vector>
#include <unordered_map>
#include <Box2D/Common/b2Math.h>

class TrackSerializer : public
				Serializer<std::unordered_map<std::string, std::vector<b2Vec2>>> {
public:
    JSON serialize_to_json(std::unordered_map<std::string,
    				std::vector<b2Vec2>>& track) override;
};


#endif //TALLER_MICROMACHINES_TRACKSERIALIZER_H
