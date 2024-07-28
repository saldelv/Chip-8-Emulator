#include "Input.h"

Input::Input()
{
    defaultSpeed = 1000/600;
    speed = defaultSpeed;
    paused = false;
    debug = false;
}

uint8_t Input::check_input(SDL_Event event)
{
    switch(event.type) 
    {
        case SDL_KEYDOWN:
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_1:
                {
                    return 1;
                }
                case SDLK_2:
                {
                    return 2;
                }
                case SDLK_3:
                {
                    return 3;
                }
                case SDLK_4:
                {
                    return 0xc;
                }
                case SDLK_q:
                {
                    return 4;
                }
                case SDLK_w:
                {
                    return 5;
                }
                case SDLK_e:
                {
                    return 6;
                }
                case SDLK_r:
                {
                    return 0xd;
                }
                case SDLK_a:
                {
                    return 7;
                }
                case SDLK_s:
                {
                    return 8;
                }
                case SDLK_d:
                {
                    return 9;
                }
                case SDLK_f:
                {
                    return 0xe;
                }
                case SDLK_z:
                {
                    return 0xa;
                }
                case SDLK_x:
                {
                    return 0;
                }
                case SDLK_c:
                {
                    return 0xb;
                }
                case SDLK_v:
                {
                    return 0xf;
                }
                case SDLK_F6:
                {
                    return 0xfd;
                }
                case SDLK_ESCAPE:
                {
                    paused = !paused;
                    break;
                }
                case SDLK_F5:
                {
                    debug = !debug;
                    break;
                }
                case SDLK_F1:
                {
                    return 0xfc;
                }
                case SDLK_F2:
                {
                    return 0xfb;
                }
                case SDLK_SPACE:
                {
                    speed = defaultSpeed / 2;
                }
                default:
                {
                    return 0xff;
                }
            }
        }
        case SDL_KEYUP:
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_SPACE:
                {
                    speed = defaultSpeed;
                    break;
                }
            }
            return 0xff;
        }
    }
    return 0xfe;
}