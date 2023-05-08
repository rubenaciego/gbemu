#include "cpu.hpp"
#include "gameboy.hpp"
#include <iostream>

CPU::CPU(GameBoy* gb) : gameboy(gb)
{
    reset();
}

void CPU::reset()
{
    if (gameboy->getModel() == GameBoy::DMG)
    {
        a = 0x01;
        f.z = 1;
        f.n = 0;
        b = 0x00;
        c = 0x13;
        d = 0x00;
        e = 0xd8;
        h = 0x01;
        l = 0x4d;
        pc = 0x0100;
        sp = 0xfffe;
    }
    else
        throw std::runtime_error("GameBoy model not implemented");
}

void CPU::execute()
{
    
}
