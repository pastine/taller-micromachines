#ifndef TALLER_MICROMACHINES_STATEUPDATER_H
#define TALLER_MICROMACHINES_STATEUPDATER_H

#include <common/Thread.h>
#include <server/ClientProxy.h>
#include <common/ProtectedQueueStatus.h>

class StateUpdater : public Thread {
private:
  ProtectedQueueStatus* queue;
  ClientProxy* messenger;
  bool running;
public:
  explicit StateUpdater(ClientProxy* messenger);

  void run() override;

  void update_status(JSON& status);

  void stop() override;

  ~StateUpdater();
};


#endif //TALLER_MICROMACHINES_STATEUPDATER_H
