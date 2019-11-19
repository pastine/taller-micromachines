//
// Created by casimiro on 17/10/19.
//

#ifndef TALLER_MICROMACHINES_SDLTEXTURELOADER_H
#define TALLER_MICROMACHINES_SDLTEXTURELOADER_H

#include "SDLTexture.h"
#include <string>
#include <map>


/*
 * This class is the one that owns the SDLTextures. It will load
 * a texture from a file once, it returns a RAII wrapper for the SDL_Textures.
 *
 * IT LEAKS MEM... we must destroy the textures :D
 */
class SDLTextureLoader {
public:
    static SDLTextureLoader *get_loader();

    static void instance_loader(SDL_Renderer *renderer);

    ~SDLTextureLoader();

    SDLTexture *get_texture(std::string &path);

    SDLTextureLoader(const SDLTextureLoader &) = delete;

    SDLTextureLoader &operator=(const SDLTextureLoader &) = delete;

private:
    explicit SDLTextureLoader(SDL_Renderer *renderer);

    void _load_from_file(std::string &path);

    std::map<std::string, SDLTexture> textures;
    static SDLTextureLoader *instance;
    SDL_Renderer *renderer;
};

/*
 Definition of the exception the texture loader might throw
class TextureLoaderException {
public:
    TextureLoaderException(const char* description);
    const char* what() const noexcept;
private:
    std::string description;
};

TextureLoaderException::TextureLoaderException(const char* description) : description(description) {}

const char* TextureLoaderException::what() const noexcept{
    return this->description.c_str();
}*/

#endif //TALLER_MICROMACHINES_SDLTEXTURELOADER_H
