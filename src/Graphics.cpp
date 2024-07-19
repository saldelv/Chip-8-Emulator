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


    //SDL_Window *window = SDL_CreateWindow("Chip 8 Emulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 64, 32, SDL_RENDERER_ACCELERATED);

    SDL_CreateWindowAndRenderer(128, 64, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Chip 8 Emulator");
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    if (NULL == window) {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
    }
}

void Graphics::update(uint32_t display[64][32])
{
    SDL_RenderClear(renderer);
    int w = 0;
    int h = 0;
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 32; j++) {
            if (display[i][j] == 0) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0.8);
            }
            else {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0.8);
            }
            SDL_RenderDrawPoint(renderer, w, h);
            SDL_RenderDrawPoint(renderer, w + 1, h);
            SDL_RenderDrawPoint(renderer, w, h + 1);
            SDL_RenderDrawPoint(renderer, w + 1, h + 1);

            h += 2;
        }
        h = 0;
        w += 2;
    }      
    SDL_RenderPresent(renderer);
}

void Graphics::stopGraphics()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
