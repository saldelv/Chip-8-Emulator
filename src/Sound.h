#pragma once

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>

class Sound
{
public:
    Sound();
    void playSound();
    void stopSound();
    void closeSound();

    SDL_AudioSpec want, have;
    SDL_AudioDeviceID dev;
};

    void SDLCALL audioCallback(void *userdata, Uint8 *stream, int len);
