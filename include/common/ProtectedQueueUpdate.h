#ifndef TALLER_MICROMACHINES_PROTECTEDQUEUEUPDATE_H
#define TALLER_MICROMACHINES_PROTECTEDQUEUEUPDATE_H


#include <queue>
#include <mutex>
#include <condition_variable>
#include "json.h"

class ProtectedQueueUpdate {
private:
	std::queue<JSON> q;
	std::mutex m;
	std::condition_variable cond_var;
	bool done;
public:
	ProtectedQueueUpdate();

	void push(JSON& json);

	JSON pop();

	void stop();

	~ProtectedQueueUpdate();
};


#endif //TALLER_MICROMACHINES_PROTECTEDQUEUEUPDATE_H
