#include <common/ClosedQueueException.h>
#include "common/ProtectedQueueStatus.h"

ProtectedQueueStatus::ProtectedQueueStatus(size_t maxsize) :
    q(std::queue<JSON>()), max_size(maxsize), done(false) {
}

void ProtectedQueueStatus::push(JSON json) {
	std::unique_lock<std::mutex> lock(this->m);
    while (this->q.size() == this->max_size) {
        this->push_var.wait(lock);
    }
	this->q.push(std::move(json));
    this->pop_var.notify_all();
}

JSON ProtectedQueueStatus::pop() {
	std::unique_lock<std::mutex> lock(this->m);
	while (this->q.empty() && ! this->done) {
		this->pop_var.wait(lock);
	}
	if (q.empty() && done) {throw ClosedQueueException("Closed Queue");}
	JSON update = std::move(q.front());
	q.pop();
    this->push_var.notify_all();
    return update;
}

void ProtectedQueueStatus::stop() {
	this->done = true;
	this->pop_var.notify_all();
}

ProtectedQueueStatus::~ProtectedQueueStatus() {
}




