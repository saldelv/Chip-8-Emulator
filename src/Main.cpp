#include "Main.h"
#include "Chip8.h"
#include "Visuals.h"
#include <iostream>
#include <stdio.h>

int main(int argv, char** args) {

    std::cout << "Hello" << std::endl;

    Visuals* visuals = new Visuals();

    if (visuals->window == NULL) {
        return -1;
    }

    Chip8* chip = new Chip8();
    

    return EXIT_SUCCESS;
}
