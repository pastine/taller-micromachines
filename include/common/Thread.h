#ifndef SRC_COMMON_THREAD_H
#define SRC_COMMON_THREAD_H


#include <thread>
#include <atomic>

class Thread {
public:
    void join();
    void start();

    virtual void stop() = 0;
    virtual void run() = 0;
    virtual ~Thread() {};
    Thread();
    Thread(const Thread&) = delete;
    Thread(Thread&&);
    Thread& operator=(const Thread&) = delete;
    Thread&operator=(Thread&&);
    std::atomic<bool> is_alive;

private:
    std::thread thread;
};


#endif //SRC_COMMON_THREAD_H
