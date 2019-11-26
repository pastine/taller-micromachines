
#ifndef TALLER_MICROMACHINES_AUDIO_H
#define TALLER_MICROMACHINES_AUDIO_H

#include <string>

class Audio {
public:
    Audio();

    static void play(std::string filename);

    static void ending();

    static void stop();
};


#endif //TALLER_MICROMACHINES_AUDIO_H
