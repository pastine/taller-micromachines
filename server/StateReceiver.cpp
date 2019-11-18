#include "server/StateReceiver.h"

StateReceiver::StateReceiver(ClientProxy* messenger) :
        queue(new ProtectedQueue<MoveType>()),
        messenger(messenger), running(true){
}

void StateReceiver::run() {
	try {
		while (running) {
			MoveType move = messenger->get_move();
			queue->push(move);
		}
	} catch (...) {
		return;
	}
}

MoveType StateReceiver::get_move() {
	return queue->pop();
}

void StateReceiver::stop() {
	running = false;
	queue->stop();
}

StateReceiver::~StateReceiver() {
	messenger = nullptr;
	delete(queue);
	this->join();
}
