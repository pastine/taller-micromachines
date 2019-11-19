//
// Created by casimiro on 17/10/19.
//

#include <iostream>
#include "client/SDLTextureLoader.h"
#include "client/SDLException.h"


SDLTextureLoader *SDLTextureLoader::instance = nullptr;

SDLTextureLoader *SDLTextureLoader::get_loader() {
    if (instance) return instance;
    throw std::runtime_error("Trying to get the TextureLoader while not being initialized");
}

void SDLTextureLoader::instance_loader(SDL_Renderer *renderer) {
    if (instance)
        throw std::runtime_error("Trying to instance already instanced TextureLoader");
    instance = new SDLTextureLoader(renderer);
}

SDLTextureLoader::SDLTextureLoader(SDL_Renderer *renderer) : renderer(renderer) {}

SDLTextureLoader::~SDLTextureLoader() {}

SDLTexture *SDLTextureLoader::get_texture(std::string &path) {
    std::map<std::string, SDLTexture>::iterator it;

    // get the SDLTexture or load it from the file
    it = this->textures.find(path);
    if (it == this->textures.end()) {
        this->_load_from_file(path);
    }
    it = this->textures.find(path);
    if (it == this->textures.end()) throw SDLException("Unexpected error in get_texture", 0);
    return &(*it).second;
}

void SDLTextureLoader::_load_from_file(std::string &path) {
    SDL_Surface *loaded_surface = IMG_Load(path.data());
    if (!loaded_surface) {
        std::string err_msg = "Couldn't load surface from: ";
        err_msg += path;
        throw SDLException(err_msg.data(), SDL_GetError());
    }

    // transform the surface to a texture
    SDL_Texture *new_texture = nullptr;
    new_texture = SDL_CreateTextureFromSurface(this->renderer, loaded_surface);
    if (!new_texture) {
        std::string err_msg = "Couldn't convert to texture from file: ";
        err_msg += path;
        throw SDLException(err_msg.data(), SDL_GetError());
    }
    SDLTexture texture(new_texture,
                       loaded_surface->w,
                       loaded_surface->h);
    this->textures.insert(std::pair<std::string, SDLTexture>(path, std::move(texture)));
    SDL_FreeSurface(loaded_surface);
}


