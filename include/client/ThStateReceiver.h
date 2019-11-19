#ifndef TALLER_MICROMACHINES_THSTATERECEIVER_H
#define TALLER_MICROMACHINES_THSTATERECEIVER_H


#include <common/Thread.h>
#include <client/ServerProxy.h>
#include <common/ProtectedQueue.h>

class ThStateReceiver : public Thread {
public:
    ThStateReceiver(ServerProxy *proxy, ProtectedQueue<JSON> *state_queue);

    void run() override;

    void stop() override;

private:
    ProtectedQueue<JSON> *state_queue;
    ServerProxy *server;
    bool done;
};


#endif //TALLER_MICROMACHINES_THSTATERECEIVER_H
