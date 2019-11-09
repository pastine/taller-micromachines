
#include <common/json.h>
#include <unordered_map>
#include "common/TrackSerializer.h"

std::string TrackSerializer::serialize(Track track) {
    JSON tracks = {
            { "straight", {
              {{"x", "0"}, {"y", "0"}, {"angle", "0"}},
              {{"x", "0"}, {"y", "80"}, {"angle", "0"}},
              {{"x", "-40"}, {"y", "40"}, {"angle", "0"}},
              {{"x", "40"}, {"y", "40"}, {"angle", "0"}} }
            },
            { "curved",  JSON::array() }
    };
    return tracks.dump();
}
