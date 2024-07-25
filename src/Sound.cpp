#include "Sound.h"

void SDLCALL audioCallback(void *userdata, Uint8 *stream, int len)
{
    
}


Sound::Sound()
{
    SDL_zero(want);
    SDL_zero(have);

    want.freq = 48000;
    want.format = AUDIO_F32;
    want.channels = 2;
    want.samples = 4096;
    want.callback = audioCallback;

    dev = SDL_OpenAudioDevice(NULL, 0, &want, &have, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
}

void Sound::playSound()
{

}

void Sound::stopSound()
{
    
}
