#include "Chip8.h"
#include "Graphics.h"
#include "Input.h"
#include <iostream>
#include <stdio.h>

int main(int argv, char** args) {

    // Initialize SDL
    SDL_SetHint("SDL_AUDIODRIVER", "directsound");
    SDL_Init(SDL_INIT_EVERYTHING);

    // check if argument is given
    const char* rom_name;
    if (args[1] != NULL) {
        rom_name =  args[1];
    }
    else {
        std::cout << "Enter a ROM name" << std::endl;
        return -1;
    }

    // initialize everything
    Input* input = new Input();
    Chip8* chip = new Chip8();

    // load rom into memory
    chip->load_rom(rom_name);

    Graphics* graphics = new Graphics();
    if (graphics->window == NULL) {
        return -1;
    }

    int cycles = 0;
    while(true) {
        // decrement sound and delay timerss at 60hz
        cycles++;
        if (cycles == 10) {
            chip->decrement_timers();
            cycles = 0;
        }

        // checking if window was closed
        if (SDL_PollEvent(&graphics->event) && SDL_QUIT == graphics->event.type) {
            break;
        }

        // getting button input
        uint8_t pressed = input->check_input(graphics->event);
        if (pressed <= 0xf || pressed == 0xff) {
            chip->key = pressed;
        }

        // checking if the game is paused or if debug mode is activated
        if (input->paused == false) {
            if (input->debug == true) {
                if (pressed == 0xfd) {
                    chip->cycle(input->debug);
                    graphics->update(chip->display);
                }
            }
            else {
                // performs and instruction and updates the graphics
                chip->cycle(input->debug);
                graphics->update(chip->display);
            }
        }
        // delay to control game speed at 600hz (or double if sped up)
        SDL_Delay(input->speed);
    }

    // cleanup
    chip->sound->closeSound();
    graphics->stopGraphics();
    SDL_Quit();
    return EXIT_SUCCESS;
}
