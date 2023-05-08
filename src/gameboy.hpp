#pragma once

#include "mbcs/mbc.hpp"
#include "rom.hpp"
#include "cpu.hpp"

class GameBoy
{
public:

    enum GBModel
    {
        DMG0, DMG, MGB,
        SGB, SGB2, CGB, AGB
    };

    GameBoy();
    GameBoy(const ROM& rom);
    ~GameBoy();

    void reset();
    void loadROM(const ROM& rom);
    
    uint8_t read(uint16_t address) const;
    void write(uint16_t address, uint8_t value);

    // UP TO CHANGE
    void tick();

    GBModel getModel() const;

private:
    GBModel model;
    CPU cpu;
    MBC* mbc;

    // MEMORY MAPPING

    // 0x0000-0x3FFF fixed bank 0 of ROM
    // 0x4000-0x7FFF switchable bank 1~N ROM
    // handled by MBC

    // 0x8000-0x9FFF VRAM
    // CGB has 2 switchable banks (TODO)
    uint8_t vram[RAM_BANK_SIZE];

    // 0xA000-0xBFFF switchable bank of external RAM
    // handled by MBC

    // 0xC000-0xDFFF WRAM
    // CGB's upper half 0xD000-0xDFFF has 1~7 switchable banks (TODO)
    uint8_t wram[RAM_BANK_SIZE];

    // 0xE000-0xFDFF mirror of 0xC000-0xDDFF
    // 0xFE00-0xFE9F Sprite Attribute Table (OAM) (TODO)
    // 0xFEA0-0xFEFF not usable
    // 0xFF00-0xF7FF I/O Registers (TODO)

    // 0xFF80-0xFFFE High RAM (Zero Page)
    uint8_t hram[127];

    // 0xFFFF Interrupt Enable
    uint8_t ie;
};
