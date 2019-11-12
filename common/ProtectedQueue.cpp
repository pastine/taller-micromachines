#include <queue>
#include <mutex>
#include <condition_variable>
#include "common/ProtectedQueue.h"
#include "common/json.h"

ProtectedQueue::ProtectedQueue(size_t max_size) : max_size(max_size) {
    this->q = std::queue<JSON>();
}

void ProtectedQueue::push(JSON block) {
    std::unique_lock<std::mutex> lock(this->m);
    while (this->q.size() == this->max_size) {  // to prevent wake ups
        this->push_var.wait(lock);
    }
    this->q.push(std::move(block));
    this->pop_var.notify_all();
}

JSON ProtectedQueue::pop() {
    std::unique_lock<std::mutex> lock(this->m);
    while (this->q.size() == 0) {  // to prevent wake ups
        this->pop_var.wait(lock);
    }
    JSON block = std::move(this->q.front());
    this->q.pop();
    this->push_var.notify_all();
    return block;
}
