#include "server/StateUpdater.h"
#define MAX 1000

StateUpdater::StateUpdater(ClientProxy* messenger) :
  queue(new ProtectedQueue<JSON>(MAX)),
  messenger(messenger), running(true){
}

void StateUpdater::run() {
  while (running) {
    JSON aux = queue->pop();
    messenger->send_state(aux);
  }
}

void StateUpdater::update_status(JSON& status) {
  queue->push(status);
}

void StateUpdater::stop() {
  running = false;
  queue->stop();
}

StateUpdater::~StateUpdater() {
  this->stop();
  delete(queue);
  this->join();
}




