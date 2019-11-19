#ifndef TALLER_MICROMACHINES_CLOSEDQUEUEEXCEPTION_H
#define TALLER_MICROMACHINES_CLOSEDQUEUEEXCEPTION_H


#include <string>

class ClosedQueueException {
private:
    std::string description;
public:
    explicit ClosedQueueException(const char *description);

    const char *what() const noexcept;
};


#endif //TALLER_MICROMACHINES_CLOSEDQUEUEEXCEPTION_H
