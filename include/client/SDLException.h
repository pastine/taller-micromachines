#ifndef TALLER_MICROMACHINES_SDLEXCEPTION_H
#define TALLER_MICROMACHINES_SDLEXCEPTION_H

#include <string>
#include <exception>


class SDLException : public std::exception {
public:
    SDLException(const char *description, const char *sdlError);

    const char *what() const noexcept;

private:
    std::string description;
};


#endif //TALLER_MICROMACHINES_SDLEXCEPTION_H
