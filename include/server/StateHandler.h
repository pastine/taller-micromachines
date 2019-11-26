#ifndef TALLER_MICROMACHINES_STATEHANDLER_H
#define TALLER_MICROMACHINES_STATEHANDLER_H

#include <common/Thread.h>
#include <common/MoveType.h>
#include <common/ProtectedQueue.h>
#include "ClientProxy.h"

template<class T>
class StateHandler : public Thread {
private:
    ProtectedQueue<T> queue;
    ClientProxy *messenger;
    bool running = true;
public:
    explicit StateHandler(ClientProxy *messenger);

    void run() override;

    void stop() override;

    T receive();

    void send(T block);

    ~StateHandler() override;

    void work();
};


#endif //TALLER_MICROMACHINES_STATEHANDLER_H
