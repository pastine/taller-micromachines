#ifndef TALLER_MICROMACHINES_THFRAMEDRAWER_H
#define TALLER_MICROMACHINES_THFRAMEDRAWER_H


#include <common/ProtectedQueue.h>
#include <client/Camera.h>
#include <client/WorldEntities.h>
#include <common/Thread.h>

class ThFrameDrawer : public Thread {
public:
    explicit ThFrameDrawer(ProtectedQueue<JSON> *state_queue, JSON &map);

    void run() override;

    void stop() override;

private:
    ProtectedQueue<JSON> *state_queue;
    Camera cam;
    WorldEntities entities;
    bool done;
    size_t frames_rendered_mud;
    void _draw_frame(JSON &json);

    bool first_time = true;

    void _add_angled_element();

    void _add_simple_element(WorldEntities::Entity entity, JSON &elements);

    bool ending_not_played = true;
};


#endif //TALLER_MICROMACHINES_THFRAMEDRAWER_H
