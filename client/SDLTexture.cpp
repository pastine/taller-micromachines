//
// Created by casimiro on 17/10/19.
//

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "SDLTexture.h"

SDLTexture::SDLTexture(SDL_Texture *texture,
                       SDL_Renderer *renderer,
                       int width,
                       int height) :
                       texture(texture),
                       renderer(renderer),
                       width(width),
                       height(height) {}

SDLTexture::~SDLTexture() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
        this->width = 0;
        this->height = 0;
    }
}

void SDLTexture::render(Area& src, Area& dest) {
    std::cout << "rendering texture...\n";
    SDL_Rect render_from = {
            src.getX(), src.getY(),
            src.getWidth(), src.getHeight()
    };
    SDL_Rect render_to = {
            dest.getX(), dest.getY(),
            dest.getWidth(), dest.getHeight()
    };
    SDL_RenderCopy(this->renderer, this->texture, &render_from, &render_to);
}