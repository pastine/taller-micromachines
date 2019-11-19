#include <iostream>
#include "client/CarLivesDrawer.h"

void CarLivesDrawer::draw_lives(int num_of_lives, SDL_Renderer *renderer) {
    int padding = 10;
    for (int i = 0; i < num_of_lives; ++i) {
        heart.render(renderer, padding + (i * 30), 20);
    }
}
