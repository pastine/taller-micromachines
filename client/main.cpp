//
// Created by casimiro on 17/10/19.
//

#include <SDL2/SDL.h>
#include <iostream>
#include "SDLException.h"
#include "Camara.h"
#include "WorldEntities.h"


int main(int argc, char** argv) {
    try {
        Camara cam;
        WorldEntities entities;

        auto i = 0;
        bool running = true;
        while (running) {
            SDL_Event event;

            cam.prepare_frame();

            entities.clean();
            entities.put(WorldEntities::Entity::CAR, 100, 700 - (i % 700), 0);
            entities.put(WorldEntities::Entity::OIL, 50, 50);
            entities.render(cam);

            if (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT:
                        running = false;
                        break;
                    case SDL_KEYDOWN: {
                        SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                        switch (keyEvent.keysym.sym) {
                            case SDLK_LEFT:
                                break;
                            case SDLK_RIGHT:
                                break;
                            case SDLK_UP:
                                break;
                            case SDLK_DOWN:
                                break;
                        }
                    }
                }
            }
            cam.show_frame();
            SDL_Delay(50);
            i += 10;
        }
    } catch (SDLException& e) {
        std::cout << e.what() << '\n';
    }
}
