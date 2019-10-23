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


int main(int argc, char** argv) {
    try {
        SDLWindow window(420, 840);
        window.fill(0xFF,0xFF,0,0xFF);

        // get the car texture
        SDLTextureLoader::instance_loader(window.get_renderer());

        Car car(window.get_renderer());
        Boulder boulder(window.get_renderer());
        Oil oil(window.get_renderer());
        Mud mud(window.get_renderer());

        window.fill(0xDE,0xB8,0x81,0xFF);

        int i = 0;
        bool running = true;
        while (running) {
            SDL_Event event;
            window.fill(0xDE,0xB8,0x81,0xFF);
            //car.render();
            boulder.render(100, 100);
            oil.render(50, 50);
            mud.render(200, 200);
            mud.render(300, 300);
            
            if (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT:
                        running = false;
                        break;
                    case SDL_KEYDOWN: {
                        SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                        switch (keyEvent.keysym.sym) {
                            case SDLK_LEFT:
                                car.turn_left();
                                break;
                            case SDLK_RIGHT:
                                car.turn_right();
                                break;
                            case SDLK_UP:
                                break;
                            case SDLK_DOWN:
                                break;
                        }
                    }
                }
            }
            window.render();
            i++;
            SDL_Delay(50);
        }
    } catch (SDLException& e) {
        std::cout << e.what() << '\n';
    }
}
