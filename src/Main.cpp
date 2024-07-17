#include "Main.h"
#include "Chip8.h"
#include <iostream>
#include <stdio.h>
#include <SDL2/SDL.h>

SDL_Window* create_window() {

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
        return NULL;
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

    return window;
}

int main(int argv, char** args) {

    std::cout << "Hello" << std::endl;

    SDL_Window* window = create_window();

    if (window == NULL) {
        exit(0);
    }

    Chip8* chip = new Chip8();
    

    return EXIT_SUCCESS;
}
