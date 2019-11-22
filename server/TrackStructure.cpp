#include "TrackStructure.h"
#include <iostream>
#include <fstream>

TrackStructure::TrackStructure() {
	std::string track_string;
	std::ifstream track_file;
	track_file.open("server/temp.txt");
	track_file >> track_string;
	track_file.close();
	track = JSON::parse(track_string);
}

JSON TrackStructure::get_track() {
	return track;
}
