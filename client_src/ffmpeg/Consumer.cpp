#include <common/ClosedQueueException.h>
#include <iostream>
#include "client/Consumer.h"
#include "common/Constants.h"

Consumer::Consumer(ProtectedQueue<std::vector<char>> &producedFrames) :
        producedFrames(producedFrames),
        videoOutput(),
        ctx(sws_getContext(CAM_WIDTH, CAM_HEIGHT,
                           AV_PIX_FMT_RGB24, CAM_WIDTH, CAM_HEIGHT,
                           AV_PIX_FMT_YUV420P, 0, 0, 0, 0)) {
}

void Consumer::run() {
    try {
        while (this->is_alive) {
            std::vector<char> frame = this->producedFrames.pop();
            for (int i = 0; i < 7; i++)
                videoOutput.writeFrame(frame.data(), ctx);
        }
    }
    catch (ClosedQueueException &e) {
        return;
    }
}

void Consumer::stop() {
    this->producedFrames.stop();
    this->is_alive = false;
}

Consumer::~Consumer() {
    videoOutput.close();
    sws_freeContext(ctx);
}