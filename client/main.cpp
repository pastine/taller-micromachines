//
// Created by casimiro on 17/10/19.
//

#include <SDL2/SDL.h>
#include <iostream>
#include "SDLWindow.h"
#include "SDLException.h"

int main (int argc, char** argv) {
    try {
        SDLWindow window(240, 480);
        //#FF6F91
        window.fill(0xFF,0x6F,0x91,SDL_ALPHA_OPAQUE);
        window.render();
        SDL_Delay(3000);
    } catch (SDLException& e) {
        std::cout << e.what() << '\n';
    }
}