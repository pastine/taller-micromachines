//
// Created by casimiro on 10/11/19.
//

#ifndef TALLER_MICROMACHINES_CARLIVESDRAWER_H
#define TALLER_MICROMACHINES_CARLIVESDRAWER_H


#include <client/Heart.h>

class CarLivesDrawer {
public:
    void draw_lives(int num_of_lives, SDL_Renderer *renderer);

private:
    Heart heart;
};


#endif //TALLER_MICROMACHINES_CARLIVESDRAWER_H
