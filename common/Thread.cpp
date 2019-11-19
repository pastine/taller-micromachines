//
// Created by casimiro on 28/9/19.
//

#include "common/Thread.h"


Thread::Thread(Thread &&other) {
    this->thread = std::move(other.thread);
    this->is_alive = true;
    other.is_alive = false;
}

Thread &Thread::operator=(Thread &&other) {
    if (this == &other) return *this;
    this->thread = std::move(other.thread);
    this->is_alive = true;
    other.is_alive = false;
    return *this;
}

void Thread::start() {
    this->is_alive = true;
    this->thread = std::thread(&Thread::run, this);
}

Thread::Thread() : is_alive(true) {}

void Thread::join() {
    this->thread.join();
}
