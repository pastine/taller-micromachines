//
// Created by casimiro on 17/10/19.
//

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "SDLWindow.h"
#include "SDLException.h"
#include "SDLTextureLoader.h"
#include "Car.h"
#include "Boulder.h"
#include "Oil.h"
#include "Mud.h"
#include "Camara.h"


int main(int argc, char** argv) {
    try {
        Camara cam;

        Car car;
        Boulder boulder;
        Oil oil;
        Mud mud;


        auto i = 0;
        bool running = true;
        while (running) {
            SDL_Event event;

            cam.prepare_frame();
            cam.render_object(boulder, 100, 100);
            cam.render_object(oil, 50, 50);
            cam.render_object(mud, 200, 200);
            cam.render_object(mud, 350, 350);
            cam.render_object(car, 100, 700 - (i % 700), 0);

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
