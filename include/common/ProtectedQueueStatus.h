#ifndef TALLER_MICROMACHINES_PROTECTEDQUEUESTATUS_H
#define TALLER_MICROMACHINES_PROTECTEDQUEUESTATUS_H


#include <queue>
#include <mutex>
#include <condition_variable>
#include "json.h"

class ProtectedQueueStatus {
private:
	std::queue<JSON> q;
    size_t max_size;
    std::mutex m;
    std::condition_variable push_var;
    std::condition_variable pop_var;
	bool done;
public:
	explicit ProtectedQueueStatus(size_t maxsize);

	void push(JSON json);

	JSON pop();

	void stop();

	~ProtectedQueueStatus();
};


#endif //TALLER_MICROMACHINES_PROTECTEDQUEUESTATUS_H
