#pragma once

#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>

class Input
{
public:
    Input();
    int check_input();

    bool keyboard[16];

    SDL_Event event;
};