//
// Created by casimiro on 18/9/19.
//

#ifndef TP2_PROTECTEDQUEUE_H
#define TP2_PROTECTEDQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include "json.h"

class ProtectedQueue {
private:
    std::queue<JSON> q;
    size_t max_size;
    std::mutex m;
    std::condition_variable push_var;
    std::condition_variable pop_var;
public:
    explicit ProtectedQueue(size_t max_size);
    void push(JSON block);
    JSON pop();
};

#endif //TP2_PROTECTEDQUEUE_H
