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


int main (int argc, char** argv) {
    try {
        SDLWindow window(1000, 840);
        window.fill(0xFF,0xFF,0,0xFF);

        // get the car texture
        SDLTextureLoader::instance_loader(window.get_renderer());

        //std::string path = "client/img/cars_transparent.png";
        //SDLTexture *car = loader->get_texture(path);
/*
        int w = 26;
        int h = 29;
        int x = 100;
        int y = 100;

        int _x = 4 + 250;

        std::vector<Area> frames;
        frames.push_back(Area(_x, 4, 26 + 3, 29));
        frames.push_back(Area(_x, 33, 26 + 3, 29));
        frames.push_back(Area(_x, 67, 26 + 3, 29));
        frames.push_back(Area(_x, 96, 26 + 3, 29));*/

        Car car(window.get_renderer());

        window.fill(0xDE,0xB8,0x81,0xFF);

        int i = 0;
        bool running = true;
        while (running) {
            SDL_Event event;
            window.fill(0xDE,0xB8,0x81,0xFF);
            car.render();
            //car->render(frames[i%4], dest);

            /*car->render(frames[0], dest);

            dest = Area(x+200, y, w*5, h*5);
            car->render(frames[1], dest);

            dest = Area(x+400, y, w*5, h*5);
            car->render(frames[2], dest);

            dest = Area(x+600, y, w*5, h*5);
            car->render(frames[3], dest);*/

            if (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT:
                        running = false;
                        break;
                    case SDL_KEYDOWN: {
                        SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                        switch(keyEvent.keysym.sym) {
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