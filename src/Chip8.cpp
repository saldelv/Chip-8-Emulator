#include "Chip8.h"

#define m_nnn(op) (op & 0x0fff) //lowest 12 bits, addr
#define m_n(op) (op & 0x000f) //lowest 4 bits, nibble
#define m_xh(op) ((op & 0xf000) >> 12) //upper 4 bits of high byte
#define m_xl(op) ((op & 0x0f00) >> 8) //lower 4 bits of high byte, x variable
#define m_yh(op) ((op & 0x00f0) >> 4) //upper 4 bits of low byte, y variable
#define m_yl(op) (op & 0x000f) //lower 4 bits of low byte
#define m_high(op) (op & 0xff00) //upper 8 bits, byte
#define m_low(op) (op & 0x00ff) //lower 8 bits, byte, kk variable

Chip8::Chip8()
{
}

void Chip8::cycle()
{
    int16_t opcode = (Memory[ProgramCounter] << 8) | Memory[ProgramCounter + 1];
    ProgramCounter += 2;

    int16_t nnn = m_nnn(opcode);
    uint8_t xh = m_xh(opcode);
    uint8_t x = m_xl(opcode);
    uint8_t y = m_yh(opcode);
    uint8_t kk = m_low(opcode);
    uint8_t n = m_n(opcode);

    switch (xh) // checks hex of first 4 bits
    {
        case 0x0:
        {
            switch (opcode) // checks opcode
            {
                case 0x00E0: // CLS
                {
                    // clear graphics display
                    break;
                }
            }
                case 0x00EE: // RET
                {
                    ProgramCounter = Stack[StackPointer];
                    StackPointer--;
                    break;
                }
            break;
        }
        case 0x1: // JP addr
        {
            ProgramCounter = nnn;
            break;
        }
        case 0x2: // CALL addr
        {
            StackPointer++;
            Stack[StackPointer] = ProgramCounter;
            ProgramCounter = nnn;
            break;
        }
        case 0x3: // SE Vx, byte
        {
            if (V[x] == kk) {
                ProgramCounter += 2;
            }
            break;
        }
        case 0x4: // SNE Vx, byte
        {
            if (V[x] != kk) {
                ProgramCounter += 2;
            }
            break;
        }
        case 0x5: // SE Vx, Vy
        {
            if (V[x] != V[y]) {
                ProgramCounter += 2;
            }
            break;
        }
        case 0x6: // LD Vx, byte
        {
            V[x] = kk;
            break;
        }
        case 0x7: // ADD Vx, byte
        {
            V[x] = V[x] + kk;
            break;
        }
        case 0x8:
        {
            switch (n) // checks hex of last 4 bits
            {
                case 0x0: // LD Vx, Vy
                {
                    V[x] = V[y];
                    break;
                }
                case 0x1: // OR Vx, Vy
                {
                    V[x] = V[x] | V[y];
                    break;
                }
                case 0x2: // AND Vx, Vy
                {
                    V[x] = V[x] & V[y];
                    break;
                }
                case 0x3: // XOR Vx, Vy
                {
                    V[x] = V[x] ^ V[y];
                    break;
                }
                case 0x4: // ADD Vx, Vy
                {
                    if (V[x] + V[y] > 255) {
                        V[F] = 1;
                    }
                    else {
                        V[F] = 0;
                    }
                    V[x] = m_low(V[x] + V[y]);
                    break;
                }
                case 0x5: // SUB Vx, Vy
                {
                    if (V[x] > V[y]) {
                        V[F] = 1;
                    }
                    else {
                        V[F] = 0;
                    }
                    V[x] = V[x] - V[y];
                    break;
                }
                case 0x6: // SHR Vx {, Vy}
                {
                    if (V[x] & 1 == 1) {
                        V[F] = 1;
                    }
                    else {
                        V[F] = 0;
                    }
                    V[x] = V[x] / 2;
                    break;
                }
                case 0x7: // SUBN Vx, Vy
                {
                    if (V[y] > V[x]) {
                        V[F] = 1;
                    }
                    else {
                        V[F] = 0;
                    }
                    V[x] = V[y] - V[x];
                    break;
                }
                case 0xE: // SHL Vx {, Vy}
                {
                    if (floor(log2(V[x])) == 1) {
                        V[F] = 1;
                    }
                    else {
                        V[F] = 0;
                    }
                    V[x] = V[x] / 2;
                    break;
                }
            }
            break;
        }
        case 0x9: // SNE Vx, Vy
        {
            if (V[x] != V[y]) {
                ProgramCounter += 2;
            }
            break;
        }
        case 0xA: // LD I, addr
        {
            I = nnn;
            break;
        }
        case 0xB: // JP V0, addr
        {
            ProgramCounter = nnn + V[0];
            break;
        }
        case 0xC: // RND Vx, byte
        {
            V[x] = (rand() % 255) & kk;
            break;
        }
        case 0xD: // DRW Vx, Vy, nibble
        {
            //display sprites
            break;
        }
        case 0xE:
        {
            switch(kk)
            {
                case 0x9e: // SKP Vx
                {
                    //check keyboard
                    break;
                }
                case 0xA1: // SKNP Vx
                {
                    //check keyboard
                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        }
        case 0xF:
        {
            switch(kk)
            {
                case 0x07: // LD Vx, DT
                {
                    V[x] = DelayTimer;
                    break;
                }
                case 0x0A: // LD Vx, K
                {
                    // wait for key
                    break;
                }
                case 0x15: // LD DT, Vx
                {
                    DelayTimer = V[x];
                    break;
                }
                case 0x18: // LD ST, Vx
                {
                    SoundTimer = V[x];
                    break;
                }
                case 0x1E: // ADD I, Vx
                {
                    I = I + V[x];
                    break;
                }
                case 0x29: // LD F, Vx
                {
                    //uses sprites
                    break;
                }
                case 0x33: // LD B, Vx
                {
                    V[I] = static_cast<int>(V[x]*1000) % 1000;
                    V[I+1] = static_cast<int>(V[x]*100) % 100;
                    V[I+2] = static_cast<int>(V[x]*10) % 10;
                    break;
                }
                case 0x55: // LD [I], Vx
                {
                    int16_t I_Index = I;
                    for (uint8_t i = 0; i <= x; i++) {
                        Memory[I_Index] = V[i];
                        I_Index++; 
                    }
                    break;
                }
                case 0x65: // LD Vx, [I]
                {
                    int16_t I_Index = I;
                    for (uint8_t i = 0; i <= x; i++) {
                        V[i] = Memory[I_Index];
                        I_Index++; 
                    }
                    break;
                }
            }
            break;
        }
    }
}