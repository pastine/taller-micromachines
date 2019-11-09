#ifndef TALLER_MICROMACHINES_STATERECEIVER_H
#define TALLER_MICROMACHINES_STATERECEIVER_H

#include <common/Thread.h>
#include <common/ProtectedQueue.h>
#include "ClientProxy.h"

class StateReceiver : public Thread {
private:
  ProtectedQueue* queue;
  ClientProxy* messenger;
  bool running;
public:
  explicit StateReceiver(ClientProxy* messenger);

  void run() override;

  void receive_status(JSON status);

  void stop() override;

  ~StateReceiver();
};


#endif //TALLER_MICROMACHINES_STATERECEIVER_H
