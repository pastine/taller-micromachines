#ifndef TALLER_MICROMACHINES_ENVIRONMENT_H
#define TALLER_MICROMACHINES_ENVIRONMENT_H


#include <Box2D/Dynamics/b2World.h>
#include <server/Track.h>
#include <server/Limit.h>
#include <server/ContactListener.h>
#include <server/Car.h>
#include "common/CommunicationConstants.h"
#include "server/TrackData.h"
#include <vector>
#include <string>
#include <unordered_map>

class Environment {
private:
	b2World world;
	Track track;
	Limit limit;
	ContactListener listener;

public:
	explicit Environment(char* file);

	void step();

	TrackData get_track_data();

	Car* create_car(unsigned long i);

	void get_elements(State &state);
};


#endif //TALLER_MICROMACHINES_ENVIRONMENT_H
