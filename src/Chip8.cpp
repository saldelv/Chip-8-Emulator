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
    ProgramCounter = 0x200;
    I = 0;
    StackPointer = 0;
    SoundTimer, DelayTimer = 0;

    for (int i = 0; i < 4096; i++) {
        Memory[i] = 0;
    }
    for (int i = 0; i < 16; i++) {
        V[i] = 0;
    }
    for (int i = 0; i < 16; i++) {
        Stack[i] = 0;
    }
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 32; j++) {
            display[i][j] = 0;
        }
    }      

    for (int i = 50; i < 80 + 50; i++) {
        Memory[i] = font[i-50];
    }
}

void Chip8::load_rom(const char* rom_name)
{
    

    char* raw;

    std::ifstream rom_file(rom_name, std::ios::in | std::ios::binary | std::ios::ate);
    if (!rom_file) {
        std::cout << "Invalid ROM name" << std::endl;
        exit(0);
    }

    std::ifstream::pos_type rom_size = rom_file.tellg();

    raw = new char[rom_size];

    rom_file.seekg(0, std::ios::beg);
    rom_file.read(raw, rom_size);
    rom_file.close();

    for (int i = 0; i < rom_size; i++) {
        Memory[512 + i] = raw[i];
    }
}

void Chip8::cycle()
{
    int16_t opcode = (Memory[ProgramCounter] << 8) | Memory[ProgramCounter + 1]; // fetch
    ProgramCounter += 2;

    int16_t nnn = m_nnn(opcode);
    uint8_t xh = m_xh(opcode);
    uint8_t x = m_xl(opcode);
    uint8_t y = m_yh(opcode);
    uint8_t kk = m_low(opcode);
    uint8_t n = m_n(opcode);

    //decode and execute
    switch (xh) // checks hex of first 4 bits 
    {
        case 0x0:
        {
            switch (opcode) // checks opcode 
            {
                case 0x00E0: // CLS
                {
                    for (int i = 0; i < 64; i++) {
                        for (int j = 0; j < 32; j++) {
                            display[i][j] = 0;
                        }
                    }                    
                    break;
                }
            }
                case 0x00EE: // RET
                {
                    ProgramCounter = Stack[StackPointer];
                    StackPointer--;
                    break;
                }
                default:
                {
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
            if (V[x] == V[y]) {
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
                    if (V[x] & 0x01 == 1) {
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
            V[F] = 0;
            for (int i = 0; i < n; i++) {
                uint8_t s = Memory[I + i]; // sprite from memory
                int32_t row = (V[y] + i) % 32; // row value that wraps arround
                for (int j = 0; j < 8; j++) {
                    int32_t col = (V[x] + j) % 64; // col value that wraps around
                    int32_t bit = (s & 0x80) >> 7; // most significant bit from the sprite to decide if the pixel should appear or not
                    if (bit == 1) {
                        if (display[col][row] == 1) {
                            display[col][row] = 0;
                        }
                        else {
                            display[col][row] = 1;
                            V[F] = 1;
                        }
                    }
                    s = s << 1; // shift to next bit of sprite
                }
            }
            break;
        }
        case 0xE:
        {
            switch(kk)
            {
                case 0x9e: // SKP Vx
                {
                    if (key == V[x]) {
                        ProgramCounter += 2;
                    }
                    break;
                }
                case 0xA1: // SKNP Vx
                {
                    if (key != V[x]) {
                        ProgramCounter += 2;
                    }
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
                    if (key == -1) {
                        ProgramCounter -= 2;
                    }
                    else {
                        V[x] = key;
                    }
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
                    I = (V[x] *5) & 0xfff;  
                    break;
                }
                case 0x33: // LD B, Vx
                {
                    V[I] = V[x] / 100;
                    V[I+1] = (V[x] / 10) % 10;
                    V[I+2] = (V[x] % 100) % 10;
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
                default:
                {
                    break;
                }
            }
            break;
        }
    }
}