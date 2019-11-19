#ifndef TALLER_MICROMACHINES_CARFRAMERESOLVER_H
#define TALLER_MICROMACHINES_CARFRAMERESOLVER_H


#include <vector>
#include "Area.h"
#include "SDLTexture.h"

class CarFrameResolver {
public:
    CarFrameResolver();

    Area &resolve_frame(int angle, bool moving);

private:
    std::vector<Area> straight_up_frames;
    std::vector<Area> straight_down_frames;
    std::vector<Area> turn_1_up_frames;
    std::vector<Area> turn_2_up_frames;
    std::vector<Area> turn_3_up_frames;
    std::vector<Area> side_frames;
    std::vector<Area> turn_1_down_frames;
    std::vector<Area> turn_2_down_frames;
    std::vector<Area> turn_3_down_frames;
    int current_frame;
};


#endif //TALLER_MICROMACHINES_CARFRAMERESOLVER_H
