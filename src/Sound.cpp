#include "Sound.h"

void SDLCALL audioCallback(void *userdata, Uint8 *stream, int len)
{
    double time = 0.0f;
    double step = 1.0f / 44100.0f;
    double freq = 440.0f * 2.0f * M_PI;

    for (int i = 0; i < len; i += sizeof(int16_t)) {
        time += step;
        int16_t value = 0x8000 * SDL_sin(time * freq);
        memcpy(&stream[i], &value, sizeof(int16_t));
    }

}


Sound::Sound()
{
    SDL_zero(want);

    want.freq = 44100;
    want.format = AUDIO_S16;
    want.channels = 1;
    want.samples = 1024;
    want.callback = audioCallback;

    dev = SDL_OpenAudioDevice(NULL, 0, &want, &have, SDL_AUDIO_ALLOW_ANY_CHANGE);
}

void Sound::playSound()
{
    SDL_PauseAudioDevice(dev, 0);
}

void Sound::stopSound()
{
    SDL_PauseAudioDevice(dev, 1);
}

void Sound::closeSound()
{
    SDL_CloseAudioDevice(dev);
} 