#ifndef TALLER_MICROMACHINES_STATEUPDATER_H
#define TALLER_MICROMACHINES_STATEUPDATER_H

#include <common/Thread.h>
#include <common/ProtectedQueue.h>
#include <server/ClientProxy.h>

class StateUpdater : public Thread {
private:
  ProtectedQueue queue;
  ClientProxy messenger;
public:
  explicit StateUpdater(ClientProxy& messenger);

  virtual void run();

  void update_status(JSON status);

  ~StateUpdater();
};


#endif //TALLER_MICROMACHINES_STATEUPDATER_H
