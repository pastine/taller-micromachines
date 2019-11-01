//
// Created by casimiro on 1/11/19.
//

#ifndef TALLER_MICROMACHINES_THFRAMEDRAWER_H
#define TALLER_MICROMACHINES_THFRAMEDRAWER_H


#include <common/ProtectedQueue.h>
#include <client/Camera.h>
#include <client/WorldEntities.h>

class ThFrameDrawer {
public:
    explicit ThFrameDrawer(ProtectedQueue* state_queue);
    void run();
private:
    ProtectedQueue* state_queue;
    Camera cam;
    WorldEntities entities;
    void _draw_frame(JSON& json);
};


#endif //TALLER_MICROMACHINES_THFRAMEDRAWER_H
