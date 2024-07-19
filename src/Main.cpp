#include "Main.h"
#include "Chip8.h"
#include "Graphics.h"
#include <iostream>
#include <stdio.h>

int main(int argv, char** args) {

    std::cout << "Hello" << std::endl;

    Graphics* graphics = new Graphics();

    if (graphics->window == NULL) {
        return -1;
    }

    Chip8* chip = new Chip8();
    
    while(true) {
        if (SDL_PollEvent(&graphics->event) && SDL_QUIT == graphics->event.type) {
            break;
        }
        else { 
            chip->cycle();
            graphics->update(chip->display);
        }
        SDL_Delay(1);
    }

    graphics->stopGraphics();
    return EXIT_SUCCESS;
}
