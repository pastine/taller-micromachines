#ifndef TALLER_MICROMACHINES_SDLTEXTURE_H
#define TALLER_MICROMACHINES_SDLTEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include "Area.h"
#include <tuple>

class SDLTexture {
public:
    SDLTexture(SDL_Texture *texture,
               int width, int height);

    ~SDLTexture();

    void free_texture();

    void render(SDL_Renderer *renderer, Area &src, Area &dest, float angle);

    void render_flipped(SDL_Renderer *renderer, Area &src, Area &dest, SDL_RendererFlip flip);

    SDLTexture(SDLTexture &&other);

    SDLTexture &operator=(SDLTexture &&other);

    SDLTexture &operator=(const SDLTexture &&other) = delete;

    SDLTexture(const SDLTexture &&other) = delete;

    void change_color(std::tuple<int, int, int> t);

private:
    SDL_Texture *texture;
    int width;
    int height;
};


#endif //TALLER_MICROMACHINES_SDLTEXTURE_H
