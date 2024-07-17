#pragma once

#include <stdio.h>
#include <iostream>
#include <random>

class Chip8
{
public:
    Chip8();
    void cycle();

    uint8_t Memory[4096]; // 4096 bytes of RAM

    int16_t V[16]; // 16 general purpose Vx registers

    int16_t Stack[16]; // stores addresses the interpreter returns to after finishing a subroutine
    int16_t StackPointer; // points to top most level of stack

    int16_t I; // stores memory addresses

    int16_t ProgramCounter; // stores currently executing address

    uint8_t DelayTimer, SoundTimer; // registers that decrement for timing

    const int16_t F = 15; // 16th register index
};