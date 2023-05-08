#pragma once

#include "core.hpp"

class GameBoy;

union flags_t
{
    uint8_t flags;

    struct
    {
        uint8_t unused : 4;
        uint8_t c : 1; // Carry flag
        uint8_t h : 1; // Half carry flag (BCD)
        uint8_t n : 1; // Subtraction flag (BCD)
        uint8_t z : 1; // Zero flag
    };
};

class CPU
{
public:
    CPU(GameBoy* gb);

    void reset();
    void execute();

    // Registers

    union
    {
        uint16_t af;

        struct
        {
            flags_t f;
            uint8_t a;
        };
    };

    union
    {
        uint16_t bc;

        struct
        {
            uint8_t c;
            uint8_t b;
        };
    };

    union
    {
        uint16_t de;

        struct
        {
            uint8_t e;
            uint8_t d;
        };
    };

    union
    {
        uint16_t hl;

        struct
        {
            uint8_t l;
            uint8_t h;
        };
    };

    uint16_t sp;
    uint16_t pc;

private:
    GameBoy* gameboy;
};
