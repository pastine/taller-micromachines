#include <iostream>
#include "common/ProtectedQueueState.h"
#include "ClosedQueueException.h"

ProtectedQueueState::ProtectedQueueState() : q(std::queue<MoveType>()),
																						 done(false) {
}

void ProtectedQueueState::push(MoveType& move) {
  std::unique_lock<std::mutex> lock(this->m);
  this->q.push(move);
  this->cond_var.notify_all();
}

MoveType ProtectedQueueState::pop() {
  std::unique_lock<std::mutex> lock(this->m);
  while (this->q.empty() && ! this->done) {
  	this->cond_var.wait(lock);
  }
  if (q.empty() && done) {throw ClosedQueueException("Closed Queue");}
	MoveType move = q.front();
	q.pop();
	return move;
}

void ProtectedQueueState::stop() {
	this->done = true;
	this->cond_var.notify_all();
}

ProtectedQueueState::~ProtectedQueueState() {
}


