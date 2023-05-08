#include "mbc.hpp"
#include "mbcnone.hpp"
#include "mbc1.hpp"
#include <iostream>

MBC* MBC::createMBC(const ROM& rom)
{
    switch (rom.cartridge)
    {
    case 0x00: return new MBCNone(rom);
    case 0x01:
    case 0x02:
    case 0x03: return new MBC1(rom);
    
    default: throw std::runtime_error("MBC " + std::to_string(rom.cartridge) + " not yet implemented");
    }

    return nullptr;
}
