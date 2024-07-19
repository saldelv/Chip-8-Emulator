#include "Main.h"
#include "Chip8.h"
#include "Graphics.h"
#include <iostream>
#include <stdio.h>

int main(int argv, char** args) {
    Graphics* graphics = new Graphics();

    if (graphics->window == NULL) {
        return -1;
    }

    Chip8* chip = new Chip8();

    //char* rom_name = args[1];
    const char* rom_name =  "test_opcode.ch8";
    chip->load_rom(rom_name);

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
