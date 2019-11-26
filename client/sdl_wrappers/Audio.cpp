
#include <SDL2/SDL.h>
#include <client/SDLException.h>
#include <SDL2/SDL_mixer.h>
#include "client/Audio.h"

Audio::Audio() {
    int err_code = SDL_Init(SDL_INIT_AUDIO);
    if (err_code) throw SDLException("Can't initialize audio", SDL_GetError());

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        throw SDLException("Can't initialize mixer", Mix_GetError());

    Mix_Music *background = Mix_LoadMUS("client/audio/background.wav");
    Mix_VolumeMusic(20);
    Mix_PlayMusic(background, -1);
}

void Audio::play(std::string filename) {
    std::string file = "client/audio/"+filename+".wav";
    Mix_Chunk *sound = Mix_LoadWAV(file.c_str());
    Mix_PlayChannel(-1, sound, 0);
}
