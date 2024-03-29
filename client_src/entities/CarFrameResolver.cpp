#include <stdexcept>
#include <client/Audio.h>
#include "client/CarFrameResolver.h"

CarFrameResolver::CarFrameResolver() {
    int w = 26;
    int h = 29;

    straight_up_frames.emplace_back(Area(4, 4, w, h));
    straight_up_frames.emplace_back(Area(4, 38, w, h));
    straight_up_frames.emplace_back(Area(4, 67, w, h));
    straight_up_frames.emplace_back(Area(4, 101, w, h));

    turn_1_up_frames.emplace_back(Area(4 + 26, 4, 26, 29));
    turn_1_up_frames.emplace_back(Area(4 + 26, 37, 26, 29));
    turn_1_up_frames.emplace_back(Area(4 + 26, 67, 26, 29));
    turn_1_up_frames.emplace_back(Area(4 + 26, 100, 26, 29));

    turn_2_up_frames.emplace_back(Area(4 + 58, 4, 26 + 3, 29));
    turn_2_up_frames.emplace_back(Area(4 + 58, 36, 26 + 3, 29));
    turn_2_up_frames.emplace_back(Area(4 + 58, 67, 26 + 3, 29));
    turn_2_up_frames.emplace_back(Area(4 + 58, 99, 26 + 3, 29));

    turn_3_up_frames.emplace_back(Area(4 + 91, 4, 26 + 3, 29));
    turn_3_up_frames.emplace_back(Area(4 + 91, 36, 26 + 3, 29));
    turn_3_up_frames.emplace_back(Area(4 + 91, 67, 26 + 3, 29));
    turn_3_up_frames.emplace_back(Area(4 + 91, 99, 26 + 3, 29));

    side_frames.emplace_back(Area(4 + 125, 4, 26 + 3, 29));
    side_frames.emplace_back(Area(4 + 125, 36, 26 + 3, 29));
    side_frames.emplace_back(Area(4 + 125, 67, 26 + 3, 29));
    side_frames.emplace_back(Area(4 + 125, 99, 26 + 3, 29));

    turn_1_down_frames.emplace_back(Area(4 + 160, 4, 26 + 3, 29));
    turn_1_down_frames.emplace_back(Area(4 + 160, 34, 26 + 3, 29));
    turn_1_down_frames.emplace_back(Area(4 + 160, 67, 26 + 3, 29));
    turn_1_down_frames.emplace_back(Area(4 + 160, 97, 26 + 3, 29));

    turn_2_down_frames.emplace_back(Area(4 + 193, 4, 26 + 3, 29));
    turn_2_down_frames.emplace_back(Area(4 + 193, 34, 26 + 3, 29));
    turn_2_down_frames.emplace_back(Area(4 + 193, 67, 26 + 3, 29));
    turn_2_down_frames.emplace_back(Area(4 + 193, 97, 26 + 3, 29));

    turn_3_down_frames.emplace_back(Area(4 + 223, 4, 26 + 3, 29));
    turn_3_down_frames.emplace_back(Area(4 + 223, 33, 26 + 3, 29));
    turn_3_down_frames.emplace_back(Area(4 + 223, 67, 26 + 3, 29));
    turn_3_down_frames.emplace_back(Area(4 + 223, 96, 26 + 3, 29));

    straight_down_frames.emplace_back(Area(4 + 250, 4, 26 + 3, 29));
    straight_down_frames.emplace_back(Area(4 + 250, 33, 26 + 3, 29));
    straight_down_frames.emplace_back(Area(4 + 250, 67, 26 + 3, 29));
    straight_down_frames.emplace_back(Area(4 + 250, 96, 26 + 3, 29));
    this->current_frame = -1;
}

Area &CarFrameResolver::resolve_frame(float angle, float speed) {
    this->current_frame++;
    if (speed < 5) this->current_frame = 1;
    if (angle <= 3) return this->straight_up_frames[this->current_frame % 4];
    if (angle > 3 && angle <= 30) return this->turn_1_up_frames[this->current_frame % 4];
    if (angle > 30 && angle <= 45) return this->turn_2_up_frames[this->current_frame % 4];
    if (angle > 45 && angle < 87) return this->turn_3_up_frames[this->current_frame % 4];
    if (angle >= 87 && angle <= 93) return this->side_frames[this->current_frame % 4];
    if (angle > 93 && angle <= 120) return this->turn_1_down_frames[this->current_frame % 4];
    if (angle > 120 && angle <= 135) return this->turn_2_down_frames[this->current_frame % 4];
    if (angle > 135 && angle < 177) return this->turn_3_down_frames[this->current_frame % 4];
    if (angle >= 177) return this->straight_down_frames[this->current_frame % 4];
    throw std::runtime_error("CarFrameResolver::resolve_frame: Invalid angle");
}
