#include "server/StateReceiver.h"

StateReceiver::StateReceiver(ClientProxy *messenger) :
        queue(new ProtectedQueue(1)),
        messenger(messenger), running(true){
}

void StateReceiver::run() {
  while (running) {
    JSON aux = queue->pop();
    messenger->send_state(aux);
  }
}

void StateReceiver::receive_status(JSON status) {
  queue->push(status);
}

void StateReceiver::stop() {
  running = false;
}

StateReceiver::~StateReceiver() {
  this->stop();
  delete(queue);
  this->join();
}
