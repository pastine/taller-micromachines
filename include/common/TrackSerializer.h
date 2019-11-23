#ifndef TALLER_MICROMACHINES_TRACKSERIALIZER_H
#define TALLER_MICROMACHINES_TRACKSERIALIZER_H


#include <string>
#include <common/Serializer.h>
#include <vector>
#include <unordered_map>
#include <Box2D/Common/b2Math.h>
#include "server/TrackData.h"

class TrackSerializer : public Serializer<TrackData> {
public:
    JSON serialize_to_json(TrackData& track) override;
};


#endif //TALLER_MICROMACHINES_TRACKSERIALIZER_H
