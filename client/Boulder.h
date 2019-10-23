//
// Created by casimiro on 22/10/19.
//

#ifndef TALLER_MICROMACHINES_BOULDER_H
#define TALLER_MICROMACHINES_BOULDER_H


#include "SDLTexture.h"
#include "Renderizable.h"

class Boulder : public Renderizable {
public:
    explicit Boulder(SDL_Renderer* renderer);
};


#endif //TALLER_MICROMACHINES_BOULDER_H
