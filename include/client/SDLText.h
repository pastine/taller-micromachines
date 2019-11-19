//
// Created by casimiro on 18/11/19.
//

#ifndef TALLER_MICROMACHINES_SDLTEXT_H
#define TALLER_MICROMACHINES_SDLTEXT_H

#include <SDL2/SDL_ttf.h>
#include <string>
#include <client/SDLTexture.h>

class SDLText {
public:
    SDLText();

    ~SDLText();

    void render_text(std::string text,
                     SDL_Renderer *renderer,
                     int px_x,
                     int px_y,
                     SDL_Color color = {0, 0, 0,});

private:
    TTF_Font *font;
};


#endif //TALLER_MICROMACHINES_SDLTEXT_H
