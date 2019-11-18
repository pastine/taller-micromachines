#include "server/StateHandler.h"
#define MAX 1000

template<class T>
StateHandler<T>::StateHandler(ClientProxy* messenger) :
        queue(new ProtectedQueue<T>()),
        messenger(messenger), running(true){
}

template<class T>
void StateHandler<T>::run() {
	try {
		while (running) {
			work();
		}
	} catch (...) {
		return;
	}
}

template<class T>
T StateHandler<T>::receive() {
	return queue->pop();
}

template<class T>
void StateHandler<T>::stop() {
	running = false;
	queue->stop();
}

template<class T>
StateHandler<T>::~StateHandler() {
	messenger = nullptr;
	delete(queue);
	this->join();
}

template<class T>
void StateHandler<T>::send(T block) {
    queue->push(block);
}

template<>
void StateHandler<JSON>::work() {
    JSON aux = queue->pop();
    messenger->send_state(aux);
}

template<>
void StateHandler<MoveType>::work() {
    MoveType block = messenger->get_move();
    queue->push(block);
}

template class StateHandler<JSON>;
template class StateHandler<MoveType>;
