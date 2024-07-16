#include "Chip8.h"

#define mask_nnn(op) (op & 0x0fff) //lowest 12 bits, addr
#define mask_n(op) (op & 0x0f) //lowest 4 bits, nibble
#define mask_xh(op) ((op & 0xf000) >> 12) //upper 4 bits of high byte
#define mask_xl(op) ((op & 0x0f00) >> 8) //lower 4 bits of high byte, x variable
#define mask_yh(op) ((op & 0x00f0) >> 4) //upper 4 bits of low byte, y variable
#define mask_yl(op) (op & 0x000f) //lower 4 bits of low byte
#define mask_high(op) (op & 0xff00) //upper 8 bits, byte
#define mask_low(op) (op & 0x00ff) //lower 8 bits, byte, kk variable

Chip8::Chip8()
{
}

void Chip8::cycle()
{
    int16_t opcode = (Memory[ProgramCounter] << 8) | Memory[ProgramCounter + 1];
    ProgramCounter += 2;

    int16_t nnn = mask_nnn(opcode);
    uint8_t xh = mask_xh(opcode);
    uint8_t x = mask_xl(opcode);
    uint8_t y = mask_yh(opcode);
    uint8_t kk = mask_low(opcode);
    uint8_t n = mask_n(opcode);
}