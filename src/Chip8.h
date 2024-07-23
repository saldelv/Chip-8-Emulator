#pragma once

#include <stdio.h>
#include <iostream>
#include <random>
#include <fstream>

#define m_nnn(op) (op & 0x0fff) //lowest 12 bits, addr
#define m_n(op) (op & 0x0f) //lowest 4 bits, nibble
#define m_xh(op) ((op & 0xf000) >> 12) //upper 4 bits of high byte
#define m_xl(op) ((op & 0x0f00) >> 8) //lower 4 bits of high byte, x variable
#define m_yh(op) ((op & 0x00f0) >> 4) //upper 4 bits of low byte, y variable
#define m_yl(op) (op & 0x000f) //lower 4 bits of low byte
#define m_high(op) ((op & 0xff00) >> 8) //upper 8 bits, byte
#define m_low(op) (op & 0x00ff) //lower 8 bits, byte, kk variable

class Chip8
{
public:
    Chip8();
    void load_rom(const char* rom);
    void cycle(bool debug);

    uint8_t Memory[4096]; // 4096 bytes of RAM

    uint8_t V[16]; // 16 general purpose Vx registers

    int16_t Stack[16]; // stores addresses the interpreter returns to after finishing a subroutine
    int16_t StackPointer; // points to top most level of stack

    int16_t I; // stores memory addresses

    int16_t ProgramCounter; // stores currently executing address

    uint8_t DelayTimer, SoundTimer; // registers that decrement for timing

    int16_t F = 0xf; // 16th register index

    uint8_t font[80] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0,
        0x20, 0x60, 0x20, 0x20, 0x70,
        0xF0, 0x10, 0xF0, 0x80, 0xF0,
        0xF0, 0x10, 0xF0, 0x10, 0xF0,
        0x90, 0x90, 0xF0, 0x10, 0x10,
        0xF0, 0x80, 0xF0, 0x10, 0xF0,
        0xF0, 0x80, 0xF0, 0x90, 0xF0,
        0xF0, 0x10, 0x20, 0x40, 0x40,
        0xF0, 0x90, 0xF0, 0x90, 0xF0,
        0xF0, 0x90, 0xF0, 0x10, 0xF0,
        0xF0, 0x90, 0xF0, 0x90, 0x90,
        0xE0, 0x90, 0xE0, 0x90, 0xE0,
        0xF0, 0x80, 0x80, 0x80, 0xF0,
        0xE0, 0x90, 0x90, 0x90, 0xE0,
        0xF0, 0x80, 0xF0, 0x80, 0xF0,
        0xF0, 0x80, 0xF0, 0x80, 0x80
    };

    uint32_t display[64][32];

    uint8_t key;
};