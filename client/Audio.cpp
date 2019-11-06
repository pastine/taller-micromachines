
#include <SDL2/SDL.h>
#include <client/SDLException.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <zconf.h>
#include "client/Audio.h"

Audio::Audio() {
    int err_code = SDL_Init(SDL_INIT_AUDIO);
    if (err_code) throw SDLException("Can't initialize audio", SDL_GetError());

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0)
        throw SDLException("Can't initialize mixer", Mix_GetError());

    std::cout << getcwd(NULL,0);
    Mix_Music *background = Mix_LoadMUS("client/audio/background.wav");
    powerup = Mix_LoadWAV("client/audio/powerup.wav");
    Mix_PlayMusic(background, -1);
}

void Audio::play() {
    Mix_PlayChannel(-1, powerup, 0);
}
