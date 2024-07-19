#include "Graphics.h"

Graphics::Graphics()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);


    SDL_Window *window = SDL_CreateWindow("Chip 8 Emulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 64, 32, SDL_RENDERER_ACCELERATED);

    if (NULL == window) {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
    }

    SDL_Event windowEvent;

    while(true) {
        if (SDL_PollEvent(&windowEvent)) {
            if (SDL_QUIT == windowEvent.type) {
                break;
            }
        }
    }
}

void Graphics::update()
{
    //update graphics
}

void Graphics::stopGraphics()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}
