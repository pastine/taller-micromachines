//
// Created by casimiro on 18/10/19.
//

#include <stdexcept>
#include "client/CarFrameResolver.h"

CarFrameResolver::CarFrameResolver() {
    int w = 26;
    int h = 29;

    straight_up_frames.push_back(Area(4, 4, w, h));
    straight_up_frames.push_back(Area(4, 38, w, h));
    straight_up_frames.push_back(Area(4, 67, w, h));
    straight_up_frames.push_back(Area(4, 101, w, h));

    turn_1_up_frames.push_back(Area(4 + 26, 4, 26, 29));
    turn_1_up_frames.push_back(Area(4 + 26, 37, 26, 29));
    turn_1_up_frames.push_back(Area(4 + 26, 67, 26, 29));
    turn_1_up_frames.push_back(Area(4 + 26, 100, 26, 29));

    turn_2_up_frames.push_back(Area(4 + 58, 4, 26 + 3, 29));
    turn_2_up_frames.push_back(Area(4 + 58, 36, 26 + 3, 29));
    turn_2_up_frames.push_back(Area(4 + 58, 67, 26 + 3, 29));
    turn_2_up_frames.push_back(Area(4 + 58, 99, 26 + 3, 29));

    turn_3_up_frames.push_back(Area(4 + 91, 4, 26 + 3, 29));
    turn_3_up_frames.push_back(Area(4 + 91, 36, 26 + 3, 29));
    turn_3_up_frames.push_back(Area(4 + 91, 67, 26 + 3, 29));
    turn_3_up_frames.push_back(Area(4 + 91, 99, 26 + 3, 29));

    side_frames.push_back(Area(4 + 125, 4, 26 + 3, 29));
    side_frames.push_back(Area(4 + 125, 36, 26 + 3, 29));
    side_frames.push_back(Area(4 + 125, 67, 26 + 3, 29));
    side_frames.push_back(Area(4 + 125, 99, 26 + 3, 29));

    turn_1_down_frames.push_back(Area(4 + 160, 4, 26 + 3, 29));
    turn_1_down_frames.push_back(Area(4 + 160, 34, 26 + 3, 29));
    turn_1_down_frames.push_back(Area(4 + 160, 67, 26 + 3, 29));
    turn_1_down_frames.push_back(Area(4 + 160, 97, 26 + 3, 29));

    turn_2_down_frames.push_back(Area(4 + 193, 4, 26 + 3, 29));
    turn_2_down_frames.push_back(Area(4 + 193, 34, 26 + 3, 29));
    turn_2_down_frames.push_back(Area(4 + 193, 67, 26 + 3, 29));
    turn_2_down_frames.push_back(Area(4 + 193, 97, 26 + 3, 29));

    turn_3_down_frames.push_back(Area(4 + 223, 4, 26 + 3, 29));
    turn_3_down_frames.push_back(Area(4 + 223, 33, 26 + 3, 29));
    turn_3_down_frames.push_back(Area(4 + 223, 67, 26 + 3, 29));
    turn_3_down_frames.push_back(Area(4 + 223, 96, 26 + 3, 29));

    straight_down_frames.push_back(Area(4 + 250, 4, 26 + 3, 29));
    straight_down_frames.push_back(Area(4 + 250, 33, 26 + 3, 29));
    straight_down_frames.push_back(Area(4 + 250, 67, 26 + 3, 29));
    straight_down_frames.push_back(Area(4 + 250, 96, 26 + 3, 29));
    this->current_frame = -1;
}

Area& CarFrameResolver::resolve_frame(int angle) {
    this->current_frame++;
    if (angle == 0) return this->straight_up_frames[this->current_frame % 4];
    if (angle <= 30) return this->turn_1_up_frames[this->current_frame % 4];
    if (angle <= 60) return this->turn_2_up_frames[this->current_frame % 4];
    if (angle < 90) return this->turn_3_up_frames[this->current_frame % 4];
    if (angle == 90) return this->side_frames[this->current_frame % 4];
    if (angle <= 120) return this->turn_1_down_frames[this->current_frame % 4];
    if (angle <= 150) return this->turn_2_down_frames[this->current_frame % 4];
    if (angle < 180) return this->turn_3_down_frames[this->current_frame % 4];
    if (angle == 180) return this->straight_down_frames[this->current_frame % 4];
    throw std::runtime_error("CarFrameResolver::resolve_frame: Invalid angle");
}
