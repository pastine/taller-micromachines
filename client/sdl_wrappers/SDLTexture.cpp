#include <SDL2/SDL.h>
#include <iostream>
#include "client/SDLTexture.h"
#include "client/SDLException.h"

SDLTexture::SDLTexture(SDL_Texture *texture,
                       int width,
                       int height) :
        texture(texture),
        width(width),
        height(height) {}

SDLTexture::~SDLTexture() {
    this->free_texture();
}

void SDLTexture::free_texture() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
        this->width = 0;
        this->height = 0;
    }
}

void SDLTexture::render_flipped(SDL_Renderer *renderer,
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
                             nullptr,
                             flip);
    if (s) {
        std::string err_msg = "Error while rendering texture";
        throw SDLException(err_msg.data(), SDL_GetError());
    }
}

void SDLTexture::render(SDL_Renderer *renderer, Area &src, Area &dest, float angle) {
    SDL_Rect render_from = {
            src.getX(), src.getY(),
            src.getWidth(), src.getHeight()
    };

    SDL_Rect render_to = {
            dest.getX(), dest.getY(),
            dest.getWidth(), dest.getHeight()
    };

    SDL_Point center = {dest.getHeight()/2, dest.getWidth()/2};

    int s = SDL_RenderCopyEx(renderer,
                             this->texture,
                             &render_from,
														 &render_to,
                             angle,
                             &center
                             ,SDL_FLIP_NONE);
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
    other.texture = nullptr;
}

SDLTexture &SDLTexture::operator=(SDLTexture &&other) {
    if (this == &other) return *this;
    this->width = other.width;
    other.width = 0;
    this->height = other.height;
    other.height = 0;
    this->texture = other.texture;
    other.texture = nullptr;
    return *this;
}

void SDLTexture::change_color(std::tuple<int, int, int> t) {
    SDL_SetTextureColorMod(this->texture, std::get<0>(t), std::get<1>(t), std::get<2>(t));
}

