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
 */
class SDLTextureLoader {
public:
    SDLTextureLoader(SDL_Renderer* renderer);
    ~SDLTextureLoader();
    SDLTexture* get_texture(std::string& path);
private:
    std::map<std::string, SDLTexture> textures;
    void _load_from_file(std::string& path);
    SDL_Renderer* renderer;
};


#endif //TALLER_MICROMACHINES_SDLTEXTURELOADER_H
