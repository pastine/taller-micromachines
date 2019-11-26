#ifndef FRAME_H
#define FRAME_H

#include <string>
extern "C" {
#include <libavutil/frame.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
}

class Frame {
private:
    AVFrame* frame;
    int currentPts;

public:
    Frame(int format, int width, int height);
    ~Frame();

    void write(const char *data, SwsContext *ctx);

    AVFrame* get() {return this->frame;}
};



#endif //FRAME_H
