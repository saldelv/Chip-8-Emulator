#include "Main.h"
#include "Chip8.h"
#include "Graphics.h"
#include "Input.h"
#include <iostream>
#include <stdio.h>

int main(int argv, char** args) {

    const char* rom_name;
    if (args[1] != NULL) {
        rom_name =  args[1];
    }
    else {
        std::cout << "Enter a ROM name" << std::endl;
        return -1;
    }

    Input* input = new Input();

    Chip8* chip = new Chip8();
    chip->load_rom(rom_name);

    Graphics* graphics = new Graphics();
    if (graphics->window == NULL) {
        return -1;
    }

    while(true) {
        if (SDL_PollEvent(&graphics->event) && SDL_QUIT == graphics->event.type) {
            break;
        }
        else { 
            chip->key = input->check_input(graphics->event);
            chip->cycle();
            graphics->update(chip->display);
        }
        SDL_Delay(input->speed);
    }

    graphics->stopGraphics();
    return EXIT_SUCCESS;
}
