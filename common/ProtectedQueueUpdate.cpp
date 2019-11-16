#include <common/ClosedQueueException.h>
#include "common/ProtectedQueueUpdate.h"

ProtectedQueueUpdate::ProtectedQueueUpdate() : q(std::queue<JSON>()),
																							 done(false) {
}

void ProtectedQueueUpdate::push(JSON &json) {
	std::unique_lock<std::mutex> lock(this->m);
	this->q.push(json);
	this->cond_var.notify_all();
}

JSON ProtectedQueueUpdate::pop() {
	std::unique_lock<std::mutex> lock(this->m);
	while (this->q.empty() && ! this->done) {
		this->cond_var.wait(lock);
	}
	if (q.empty() && done) {throw ClosedQueueException("Closed Queue");}
	JSON update = q.front();
	q.pop();
	return update;
}

void ProtectedQueueUpdate::stop() {
	this->done = true;
	this->cond_var.notify_all();
}

ProtectedQueueUpdate::~ProtectedQueueUpdate() {
}




