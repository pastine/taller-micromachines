#ifndef CONSUMER_H
#define CONSUMER_H

#include "common/Thread.h"
#include "common/ProtectedQueue.h"
#include "Output.h"
#include <vector>
extern "C" {
#include <libswscale/swscale.h>
}

class Consumer : public Thread  {
private:
    ProtectedQueue<std::vector<char>>& producedFrames;
    Output videoOutput;
    SwsContext* ctx;

public:
    /// first you need to Initialize libavformat and register all the muxers, demuxers and
    /// protocols with av_register_all();
    Consumer(ProtectedQueue<std::vector<char>>& producedImages);

    ~Consumer();

    virtual void run() override;
    virtual void stop() override {};

};


#endif //CONSUMER_H
