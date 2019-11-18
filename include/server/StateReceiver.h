#ifndef TALLER_MICROMACHINES_STATERECEIVER_H
#define TALLER_MICROMACHINES_STATERECEIVER_H

#include <common/Thread.h>
#include <common/MoveType.h>
#include <common/ProtectedQueue.h>
#include "ClientProxy.h"

class StateReceiver : public Thread {
private:
	ProtectedQueue<MoveType>* queue;
	ClientProxy* messenger;
	bool running;
public:
	explicit StateReceiver(ClientProxy* messenger);

	void run() override;

	void stop() override;

	MoveType get_move();

	~StateReceiver();
};


#endif //TALLER_MICROMACHINES_STATERECEIVER_H
