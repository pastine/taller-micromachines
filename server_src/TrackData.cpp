#include "server/TrackData.h"

TrackData::TrackData(
        std::unordered_map<std::string, std::vector<b2Vec2>> elements,
        JSON roads) : static_elements(std::move(elements)),
                      track(std::move(roads)) {
}

std::unordered_map<std::string, std::vector<b2Vec2>> TrackData::get_elements() {
    return static_elements;
}

JSON TrackData::get_track() {
    return track;
}


