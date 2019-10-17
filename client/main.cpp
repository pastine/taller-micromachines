//
// Created by casimiro on 17/10/19.
//

#include <SDL2/SDL.h>
#include <iostream>
#include "SDLWindow.h"
#include "SDLException.h"
#include "SDLTextureLoader.h"


int main (int argc, char** argv) {
    try {
        SDLWindow window(840, 840);

        SDLTextureLoader loader(window.ger_renderer());
        std::string path = "client/img/cars_transparent.png";
        SDLTexture *car = loader.get_texture(path);

        int w = 100;
        int h = 100;

        Area src(0, 0, w, h);
        Area dest(100, 100, w*4, h*4);
        window.fill(0xFF,0xFF,0,0xFF);
        car->render(src, dest);
        window.render();

        SDL_Delay(3000);


    } catch (SDLException& e) {
        std::cout << e.what() << '\n';
    }
}