#ifndef TALLER_MICROMACHINES_TRACKSERIALIZER_H
#define TALLER_MICROMACHINES_TRACKSERIALIZER_H


#include <string>
#include <server/Track.h>
#include <common/Serializer.h>

class TrackSerializer : public Serializer<Track> {
public:
    JSON serialize_to_json(Track &track) override;
};


#endif //TALLER_MICROMACHINES_TRACKSERIALIZER_H
