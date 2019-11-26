#ifndef SWSContext
#define SWSContext

#include <vector>
#include <client/SDLWindow.h>
#include "common/ProtectedQueue.h"

class SwsContext {
private:
    std::vector<char> dataBuffer;
    ProtectedQueue<std::vector<char>>& producedFrames;

public:
    SwsContext(ProtectedQueue<std::vector<char>>& producedFrames);
    void write(SDLWindow& window);
};



#endif //SWSContext
