#ifndef TALLER_MICROMACHINES_TRACKSERIALIZER_H
#define TALLER_MICROMACHINES_TRACKSERIALIZER_H


#include <string>
#include <server/Track.h>

class TrackSerializer {
public:
    std::string serialize(Track track);
};


#endif //TALLER_MICROMACHINES_TRACKSERIALIZER_H
