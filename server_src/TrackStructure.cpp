#include "server/TrackStructure.h"
#include <iostream>
#include <fstream>

TrackStructure::TrackStructure(char *file) {
    std::string track_string;
    std::ifstream track_file;
    track_file.open(file);
    track_file >> track_string;
    track_file.close();
    track = JSON::parse(track_string);
}

JSON TrackStructure::get_track() {
    auto aux = track;
    return aux;
}
