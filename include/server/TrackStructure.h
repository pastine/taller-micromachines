#ifndef TALLER_MICROMACHINES_TRACKSTRUCTURE_H
#define TALLER_MICROMACHINES_TRACKSTRUCTURE_H


#include <common/json.h>

class TrackStructure {
private:
	JSON track;
public:
	explicit TrackStructure(char* file);

	JSON get_track();

	~TrackStructure() = default;
};


#endif //TALLER_MICROMACHINES_TRACKSTRUCTURE_H
