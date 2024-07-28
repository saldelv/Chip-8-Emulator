#include "Graphics.h"

Graphics::Graphics()
{
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);


    //SDL_Window *window = SDL_CreateWindow("Chip 8 Emulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 64, 32, SDL_RENDERER_ACCELERATED);

    SDL_CreateWindowAndRenderer(1024, 512, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Chip 8 Emulator");
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_SetWindowResizable(window, SDL_TRUE);
    SDL_RenderSetLogicalSize(renderer, 64, 32);

    if (NULL == window) {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
    }
}

void Graphics::update(uint32_t Display[64][32])
{
    SDL_RenderClear(renderer);
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 32; j++) {
            if (Display[i][j] == 0) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0.8);
            }
            else {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0.8);
            }
            SDL_RenderDrawPoint(renderer, i, j);
        }
    }      
    SDL_RenderPresent(renderer);
}

void Graphics::stopGraphics()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
