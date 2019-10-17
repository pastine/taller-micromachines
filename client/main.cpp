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
        SDLWindow window(1020, 840);

        std::cout << "about to render car\n";
        SDLTextureLoader loader(window.ger_renderer());
        std::string path = "client/img/foo.png";
        SDLTexture *car = loader.get_texture(path);

        Area src(0, 0, 64, 205);
        Area dest(520, 840, 64, 205);
        window.fill(0,100,0,0xFF);
        car->render(src, dest);
        window.render();

        SDL_Delay(3000);


    } catch (SDLException& e) {
        std::cout << e.what() << '\n';
    }
}