#include "Input.h"

Input::Input()
{

}

int Input::check_input()
{
    switch(event.type) 
    {
        case SDL_KEYDOWN:
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_1:
                {
                    keyboard[0] = true;
                    return 1;
                    break;
                }
                case SDLK_2:
                {
                    keyboard[1] = true;
                    return 2;
                    break;
                }
                case SDLK_3:
                {
                    keyboard[2] = true;
                    return 3;
                    break;
                }
                case SDLK_4:
                {
                    keyboard[3] = true;
                    return 0xc;
                    break;
                }
                case SDLK_q:
                {
                    keyboard[4] = true;
                    return 4;
                    break;
                }
                case SDLK_w:
                {
                    keyboard[5] = true;
                    return 5;
                    break;
                }
                case SDLK_e:
                {
                    keyboard[6] = true;
                    return 6;
                    break;
                }
                case SDLK_r:
                {
                    keyboard[7] = true;
                    return 0xd;
                    break;
                }
                case SDLK_a:
                {
                    keyboard[8] = true;
                    return 7;
                    break;
                }
                case SDLK_s:
                {
                    keyboard[9] = true;
                    return 8;
                    break;
                }
                case SDLK_d:
                {
                    keyboard[10] = true;
                    return 9;
                    break;
                }
                case SDLK_f:
                {
                    keyboard[11] = true;
                    return 0xe;
                    break;
                }
                case SDLK_z:
                {
                    keyboard[12] = true;
                    return 0xa;
                    break;
                }
                case SDLK_x:
                {
                    keyboard[13] = true;
                    return 0;
                    break;
                }
                case SDLK_c:
                {
                    keyboard[14] = true;
                    return 0xb;
                    break;
                }
                case SDLK_v:
                {
                    keyboard[15] = true;
                    return 0xf;
                    break;
                }
                default:
                {
                    return -1;
                    break;
                }
            }
        }
        case SDL_KEYUP:
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_1:
                {
                    keyboard[0] = false;
                    break;
                }
                case SDLK_2:
                {
                    keyboard[1] = false;
                    break;
                }
                case SDLK_3:
                {
                    keyboard[2] = false;
                    break;
                }
                case SDLK_4:
                {
                    keyboard[3] = false;
                    break;
                }
                case SDLK_q:
                {
                    keyboard[4] = false;
                    break;
                }
                case SDLK_w:
                {
                    keyboard[5] = false;
                    break;
                }
                case SDLK_e:
                {
                    keyboard[6] = false;
                    break;
                }
                case SDLK_r:
                {
                    keyboard[7] = false;
                    break;
                }
                case SDLK_a:
                {
                    keyboard[8] = false;
                    break;
                }
                case SDLK_s:
                {
                    keyboard[9] = false;
                    break;
                }
                case SDLK_d:
                {
                    keyboard[10] = false;
                    break;
                }
                case SDLK_f:
                {
                    keyboard[11] = false;
                    break;
                }
                case SDLK_z:
                {
                    keyboard[12] = false;
                    break;
                }
                case SDLK_x:
                {
                    keyboard[13] = false;
                    break;
                }
                case SDLK_c:
                {
                    keyboard[14] = false;
                    break;
                }
                case SDLK_v:
                {
                    keyboard[15] = false;
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
    }
    return -1;
}