#ifndef TALLER_MICROMACHINES_PROTECTEDQUEUE_H
#define TALLER_MICROMACHINES_PROTECTEDQUEUE_H


#include <queue>
#include <mutex>
#include <condition_variable>

template <class T> class ProtectedQueue {
private:
	std::queue<T> q;
	std::mutex m;
	std::condition_variable cond_var;
	bool done;
public:
	ProtectedQueue();

	void push(T block);

	T pop();

	void stop();

	~ProtectedQueue();
};


#endif //TALLER_MICROMACHINES_PROTECTEDQUEUE_H
