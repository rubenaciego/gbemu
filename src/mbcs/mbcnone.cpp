#include "mbcnone.hpp"
#include <iostream>
#include <cstring>

MBCNone::MBCNone(const ROM& rom)
{
    std::copy(rom.rom.begin(), rom.rom.end(), this->rom);
}

uint8_t MBCNone::read(uint16_t address) const
{
    if (address < 0x8000)
        return rom[address];
    else if (address >= 0xa000 & address < 0xc000)
        return ram[address - 0xa000];

    std::cerr << "W: Reading invalid memory region " << std::hex
        << address << std::dec << std::endl;

    return 0;
}

void MBCNone::write(uint16_t address, uint8_t value)
{
    if (address >= 0xa000 & address < 0xc000)
        ram[address - 0xa000] = value;
    else
    {
        std::cerr << "W: Writing to invalid memory region " << std::hex
            << address << std::dec << std::endl;
    }
}

const std::string& MBCNone::getName() const
{
    return name;
}
