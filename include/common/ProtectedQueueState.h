#ifndef TALLER_MICROMACHINES_PROTECTEDQUEUESTATE_H
#define TALLER_MICROMACHINES_PROTECTEDQUEUESTATE_H


#include <common/MoveType.h>
#include <queue>
#include <mutex>
#include <condition_variable>

class ProtectedQueueState {
  private:
    std::queue<MoveType> q;
    std::mutex m;
    std::condition_variable cond_var;
    bool done;
  public:
    ProtectedQueueState();

    void push(MoveType& move);

    MoveType pop();

    void stop();

    ~ProtectedQueueState();
};


#endif //TALLER_MICROMACHINES_PROTECTEDQUEUESTATE_H