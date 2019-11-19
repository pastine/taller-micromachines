#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include "client/SDLWindow.h"
#include "client/SDLException.h"

SDLWindow::SDLWindow(int width, int height) : width(width), height(height) {
    int err_code = SDL_Init(SDL_INIT_VIDEO);
    if (err_code) throw SDLException("Can't initialize window", SDL_GetError());

    uint32_t flags = SDL_RENDERER_SOFTWARE;
    flags |= SDL_WINDOW_MINIMIZED;
    flags |= SDL_WINDOW_RESIZABLE;

    err_code = SDL_CreateWindowAndRenderer(this->width,
                                           this->height,
                                           flags,
                                           &this->window,
                                           &this->renderer);
    if (err_code) throw SDLException("Can't create window", SDL_GetError());
}

SDLWindow::~SDLWindow() {
    if (this->renderer) {
        SDL_DestroyRenderer(this->renderer);
        this->renderer = nullptr;
    }
    if (this->window) {
        SDL_DestroyWindow(this->window);
        this->window = nullptr;
    }
}

void SDLWindow::fill(int r, int g, int b, int alpha) {
    SDL_SetRenderDrawColor(this->renderer, r, g, b, alpha);
    SDL_RenderClear(this->renderer);
}

void SDLWindow::render() {
    SDL_RenderPresent(this->renderer);
}

SDL_Renderer *SDLWindow::get_renderer() const {
    return this->renderer;
}

int SDLWindow::get_width() {
    SDL_GetWindowSize(this->window, &this->width, &this->height);
    return this->width;
}

int SDLWindow::get_height() {
    SDL_GetWindowSize(this->window, &this->width, &this->height);
    return this->height;
}
