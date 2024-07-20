#pragma once

#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>

class Input
{
public:
    Input();
    uint8_t check_input(SDL_Event event);
};