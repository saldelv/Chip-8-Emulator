#pragma once

#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>

class Graphics
{
public:
    Graphics();
    void update(uint32_t Display[64][32]);
    void stopGraphics();

    SDL_Window *window;

    SDL_Renderer *renderer;

    SDL_Event event;
};