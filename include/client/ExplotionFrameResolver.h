#ifndef TALLER_MICROMACHINES_EXPLOTIONFRAMERESOLVER_H
#define TALLER_MICROMACHINES_EXPLOTIONFRAMERESOLVER_H


#include <client/Area.h>
#include <vector>

class ExplotionFrameResolver {
public:
    ExplotionFrameResolver();
    Area &resolve_frame();
    bool is_done();
private:
    std::vector<Area> frames;
    size_t current_frame;
};


#endif //TALLER_MICROMACHINES_EXPLOTIONFRAMERESOLVER_H
