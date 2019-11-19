#include "common/ClosedQueueException.h"

ClosedQueueException::ClosedQueueException(const char *description) :
        description(description) {
}

const char *ClosedQueueException::what() const noexcept {
    return this->description.c_str();
}

