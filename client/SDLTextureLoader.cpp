//
// Created by casimiro on 17/10/19.
//

#include <iostream>
#include "SDLTextureLoader.h"
#include "SDLException.h"


SDLTextureLoader::SDLTextureLoader(SDL_Renderer *renderer) : renderer(renderer)
{}

SDLTextureLoader::~SDLTextureLoader() {}

SDLTexture* SDLTextureLoader::get_texture(std::string &path) {
    std::map<std::string, SDLTexture>::iterator it;

    // get the SDLTexture or load it from the file
    it = this->textures.find(path);
    if (it == this->textures.end()) {
        std::cout << "loading texture\n";
        this->_load_from_file(path);
    }
    it = this->textures.find(path);
    return &(*it).second;
}

void SDLTextureLoader::_load_from_file(std::string &path) {
    SDL_Surface* loaded_surface = IMG_Load(path.data());
    if (!loaded_surface) {
        std::string err_msg = "Couldn't load surface from: ";
        err_msg += path;
        throw SDLException(err_msg.data(), SDL_GetError());
    }

    // transform the surface to a texture
    SDL_Texture* new_texture = nullptr;
    new_texture = SDL_CreateTextureFromSurface(this->renderer, loaded_surface);
    if (!new_texture) {
        std::string err_msg = "Couldn't convert to texture from file: ";
        err_msg += path;
        throw SDLException(err_msg.data(), SDL_GetError());
    }
    SDLTexture texture(new_texture,
                       this->renderer,
                       loaded_surface->w,
                       loaded_surface->h);
    this->textures.insert(std::pair<std::string, SDLTexture>(path, texture));
    SDL_FreeSurface(loaded_surface);
}