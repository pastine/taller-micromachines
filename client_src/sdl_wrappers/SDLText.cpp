#include "client/SDLText.h"
#include <string>
#include <SDL2/SDL_render.h>
#include "client/SDLException.h"

#include <SDL2/SDL_ttf.h>


#define FONT_FILE "client_src/fonts/8bitfont.ttf"


SDLText::SDLText() {
    if (TTF_Init() != 0) {
        std::string err_msg = "Could not initialize TTF";
        std::string err = TTF_GetError();
        throw SDLException(err_msg.data(), err.data());
    }

    this->font = TTF_OpenFontIndex(FONT_FILE, 26, 0);
    if (!this->font) {
        std::string sdl_err = TTF_GetError();
        std::string err = "Could not open font";
        throw SDLException(err.data(), sdl_err.data());
    }
}

void SDLText::render_text(std::string text,
                          SDL_Renderer *renderer,
                          int px_x,
                          int px_y,
                          SDL_Color color) {
    SDL_Surface *surface = TTF_RenderText_Solid(this->font, text.data(), color);
    if (!surface) {
        std::string err_msg = "Cant create surface from text";
        std::string sdl_err = TTF_GetError();
        throw SDLException(err_msg.data(), sdl_err.data());
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    int w = surface->w;
    int h = surface->h;
    SDL_FreeSurface(surface);

    if (!texture) {
        std::string err_msg = "Cant create texture from surface";
        std::string sdl_err = SDL_GetError();
        throw SDLException(err_msg.data(), sdl_err.data());
    }

    SDL_Rect renderQuad = {px_x, px_y, w, h};
    SDL_RenderCopy(renderer, texture, nullptr, &renderQuad);
    SDL_DestroyTexture(texture);
}

SDLText::~SDLText() {
    TTF_CloseFont(this->font);
}
