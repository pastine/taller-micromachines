#include <string>
#include "client/SDLException.h"

SDLException::SDLException(const char* description, const char* sdlError)
        : description(description) {
    this->description.append("\n SDL_ERROR: ").append(sdlError);
}

const char* SDLException::what() const noexcept{
    return this->description.c_str();
}
