#ifndef TALLER_MICROMACHINES_THFRAMEDRAWER_H
#define TALLER_MICROMACHINES_THFRAMEDRAWER_H

#define FRAMES_TO_SKIP 10
#include <common/ProtectedQueue.h>
#include <client/Camera.h>
#include <client/WorldEntities.h>
#include <common/Thread.h>
#include "client/SwsContext.h"
#include "client/Consumer.h"
extern "C" {
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

class ThFrameDrawer : public Thread {
public:
    explicit ThFrameDrawer(ProtectedQueue<JSON> *state_queue, JSON &map);

    void run() override;

    void stop() override;

    Camera cam;

    void toggle_record();

private:
    ProtectedQueue<JSON> *state_queue;
    WorldEntities entities;
    bool done;
    size_t frames_rendered_mud;
    void _draw_frame(JSON &json);

    bool first_time = true;

    void _add_angled_element();

    void _add_simple_element(WorldEntities::Entity entity, JSON &elements);

    bool ending_not_played = true;

    ProtectedQueue<std::vector<char>> record_queue;
    SDL_Texture *videoTexture;
    SwsContext ctx;
    int recordFrame = FRAMES_TO_SKIP;
    bool recording = false;
    Consumer consumer;
};


#endif //TALLER_MICROMACHINES_THFRAMEDRAWER_H
