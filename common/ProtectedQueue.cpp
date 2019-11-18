#include <common/ClosedQueueException.h>
#include "common/ProtectedQueue.h"
#include <common/json.h>
#include <common/MoveType.h>

template <class T>
ProtectedQueue<T>::ProtectedQueue(size_t maxsize) :
    q(std::queue<T>()), max_size(maxsize), done(false) {
}

template <class T>
void ProtectedQueue<T>::push(T block) {
	std::unique_lock<std::mutex> lock(this->m);
    while (this->q.size() == this->max_size) {
        this->push_var.wait(lock);
    }
	this->q.push(std::move(block));
    this->pop_var.notify_all();
}

template <class T>
T ProtectedQueue<T>::pop() {
	std::unique_lock<std::mutex> lock(this->m);
	while (this->q.empty() && ! this->done) {
		this->pop_var.wait(lock);
	}
	if (q.empty() && done) {throw ClosedQueueException("Closed Queue");}
	T update = std::move(q.front());
	q.pop();
    this->push_var.notify_all();
    return update;
}

template <class T>
void ProtectedQueue<T>::stop() {
	this->done = true;
	this->pop_var.notify_all();
}

template <class T>
ProtectedQueue<T>::~ProtectedQueue() {
}

template class ProtectedQueue<JSON>;
template class ProtectedQueue<MoveType>;
