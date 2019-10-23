//
// Created by casimiro on 17/10/19.
//

#include <SDL2/SDL.h>
#include <iostream>
#include "SDLTexture.h"
#include "SDLException.h"

SDLTexture::SDLTexture(SDL_Texture *texture,
                       int width,
                       int height) :
                       texture(texture),
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

void SDLTexture::render_flipped(SDL_Renderer* renderer,
                                Area &src, Area &dest,
                                SDL_RendererFlip flip) {
    SDL_Rect render_from = {
            src.getX(), src.getY(),
            src.getWidth(), src.getHeight()
    };
    SDL_Rect render_to = {
            dest.getX(), dest.getY(),
            dest.getWidth(), dest.getHeight()
    };
    int s = SDL_RenderCopyEx(renderer,
                             this->texture,
                             &render_from,
                             &render_to,
                             0,
                             NULL,
                             flip);
    if (s) {
        std::string err_msg = "Error while rendering texture";
        throw SDLException(err_msg.data(), SDL_GetError());
    }
}

void SDLTexture::render(SDL_Renderer* renderer, Area& src, Area& dest) {
    SDL_Rect render_from = {
            src.getX(), src.getY(),
            src.getWidth(), src.getHeight()
    };
    SDL_Rect render_to = {
            dest.getX(), dest.getY(),
            dest.getWidth(), dest.getHeight()
    };
    int s = SDL_RenderCopy(renderer,
                           this->texture,
                           &render_from,
                           &render_to);
    if (s) {
        std::string err_msg = "Error while rendering texture";
        throw SDLException(err_msg.data(), SDL_GetError());
    }
}

SDLTexture::SDLTexture(SDLTexture &&other) {
    this->width = other.width;
    other.width = 0;
    this->height = other.height;
    other.height = 0;
    this->texture = other.texture;
    other.texture = NULL;
}

SDLTexture &SDLTexture::operator=(SDLTexture &&other) {
    if (this == &other) return *this;
    this->width = other.width;
    other.width = 0;
    this->height = other.height;
    other.height = 0;
    this->texture = other.texture;
    other.texture = NULL;
    return *this;
}