#include "Main.h"
#include <iostream>
#include <stdio.h>
#include <SDL2/SDL.h>

#define mask_nnn(op) (op & 0x0fff) //lowest 12 bits, addr
#define mask_n(op) (op & 0x0f) //lowest 4 bits, nibble
#define mask_xh(op) ((op & 0xf000) >> 12) //upper 4 bits of high byte
#define mask_xl(op) ((op & 0x0f00) >> 8) //lower 4 bits of high byte, x variable
#define mask_yh(op) ((op & 0x00f0) >> 4) //upper 4 bits of low byte, y variable
#define mask_yl(op) (op & 0x000f) //lower 4 bits of low byte
#define mask_high(op) (op & 0xff00) //upper 8 bits, byte
#define mask_low(op) (op & 0x00ff) //lower 8 bits, byte, kk variable


int main(int argv, char** args) {

    uint8_t Memory[4096]; // 4096 bytes of RAM
    int16_t V[16]; // general purpose Vx registers
    int16_t Stack[16]; // stores addresses the interpreter returns to after finishing a subroutine
    int16_t StackPointer; // points to top most level of stack
    int16_t I; // stores memory addresses
    int16_t ProgramCounter; // stores currently executing address
    uint8_t DelayTimer, SoundTimer; // registers that decrement for timing

    int16_t opcode = (Memory[ProgramCounter] << 8) | Memory[ProgramCounter + 1];
    ProgramCounter += 2;

    int16_t nnn = mask_nnn(opcode);
    uint8_t xh = mask_xh(opcode);
    uint8_t x = mask_xl(opcode);
    uint8_t y = mask_yh(opcode);
    uint8_t kk = mask_low(opcode);
    uint8_t n = mask_n(opcode);
    


    std::cout << "Hello" << std::endl;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);


    SDL_Window *window = SDL_CreateWindow("Chip 8 Emulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_RENDERER_ACCELERATED);

    if (NULL == window) {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Event windowEvent;

    while(true) {
        if (SDL_PollEvent(&windowEvent)) {
            if (SDL_QUIT == windowEvent.type) {
                break;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
