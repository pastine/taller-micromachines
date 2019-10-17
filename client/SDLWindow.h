//
// Created by casimiro on 17/10/19.
//

#ifndef TALLER_MICROMACHINES_SDLWINDOW_H
#define TALLER_MICROMACHINES_SDLWINDOW_H


class SDLWindow {
public:
    SDLWindow(int width, int height);
    ~SDLWindow();
    void fill(int r, int g, int b, int alpha);
    void render();
    SDL_Renderer* ger_renderer() const;
private:
    int width;
    int height;
    SDL_Window* window;
    SDL_Renderer* renderer;
};


#endif //TALLER_MICROMACHINES_SDLWINDOW_H
