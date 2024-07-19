#pragma once

#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>

class Graphics
{
public:
    Graphics();
    void update();
    void stopGraphics();

    SDL_Window* window;
};