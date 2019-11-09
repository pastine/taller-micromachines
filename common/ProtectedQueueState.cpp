#include "ProtectedQueueState.h"

ProtectedQueueState::ProtectedQueueState() {
  this->q = std::queue<MoveType>();
}

void ProtectedQueueState::push(MoveType& move) {
  std::unique_lock<std::mutex> lock(this->m);
  this->q.push(move);
  this->cond_var.notify_all();
}

MoveType ProtectedQueueState::pop() {
  std::unique_lock<std::mutex> lock(this->m);
  while (this->q.empty()) {
    this->cond_var.wait(lock);
  }
  MoveType move = std::move(q.front());
  q.pop();
  return move;
}


