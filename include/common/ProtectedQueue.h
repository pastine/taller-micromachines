#ifndef TALLER_MICROMACHINES_PROTECTEDQUEUE_H
#define TALLER_MICROMACHINES_PROTECTEDQUEUE_H


#include <queue>
#include <mutex>
#include <condition_variable>

template <class T> class ProtectedQueue {
private:
	std::queue<T> q;
    size_t max_size;
    std::mutex m;
    std::condition_variable push_var;
    std::condition_variable pop_var;
	bool done;
public:
	explicit ProtectedQueue(size_t maxsize);

	void push(T block);

	T pop();

	void stop();

	~ProtectedQueue();
};


#endif //TALLER_MICROMACHINES_PROTECTEDQUEUE_H
