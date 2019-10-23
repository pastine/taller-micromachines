//
// Created by casimiro on 23/10/19.
//

#ifndef TALLER_MICROMACHINES_MUD_H
#define TALLER_MICROMACHINES_MUD_H


#include <SDL2/SDL_system.h>
#include "Renderizable.h"

class Mud : public Renderizable{
public:
    explicit Mud(SDL_Renderer* renderer);
};


#endif //TALLER_MICROMACHINES_MUD_H
