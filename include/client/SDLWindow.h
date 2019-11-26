#ifndef TALLER_MICROMACHINES_SDLWINDOW_H
#define TALLER_MICROMACHINES_SDLWINDOW_H

#include <SDL2/SDL.h>

class SDLWindow {
public:
    SDLWindow(int width, int height);

    ~SDLWindow();

    void fill(int r, int g, int b, int alpha);

    void render();

    SDL_Renderer *get_renderer();

    int get_width();

    int get_height();

private:
    int width;
    int height;
    SDL_Window *window;
    SDL_Renderer *renderer;
};


#endif //TALLER_MICROMACHINES_SDLWINDOW_H
