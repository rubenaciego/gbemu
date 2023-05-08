#include "mbc1.hpp"
#include <iostream>

MBC1::MBC1(const ROM& rom)
{
    battery = (rom.version == 0x03);
    rom_banks.resize(rom.rom_banks);
    ram_banks.resize(rom.ram_banks);

    rom_bank_5bit = 1;
    banking_2bit = 0;
    ram_enable = false;
    advanced_banking_mode = false;
}

uint8_t MBC1::read(uint16_t address) const
{
    uint8_t rom_mask = rom_banks.size() - 1;
    uint8_t ram_mask = ram_banks.size() - 1;

    if (address < 0x4000)
    {
        uint8_t bank = (advanced_banking_mode ? (banking_2bit << 5) : 0) & rom_mask;
        return rom_banks[bank][address];
    }
    else if (address >= 0x4000 && address < 0x8000)
    {
        uint8_t bank = (rom_bank_5bit | (banking_2bit << 5)) & rom_mask;
        return rom_banks[bank][address - 0x4000];
    }
    else if (address >= 0xa000 & address < 0xc000 && ram_banks.size())
    {
        uint8_t bank = (advanced_banking_mode ? banking_2bit : 0) & ram_mask;
        return ram_banks[bank][address - 0xa000];
    }

    std::cerr << "W: Reading invalid memory region " << std::hex
        << address << std::dec << std::endl;
    
    return 0;
}

void MBC1::write(uint16_t address, uint8_t value)
{
    uint8_t ram_mask = ram_banks.size() - 1;

    if (address < 0x2000)
        ram_enable = ((value & 0x0f) == 0x0a);
    else if (address >= 0x2000 && address < 0x4000)
        rom_bank_5bit = std::max(1, value & 0x1f);
    else if (address >= 0x4000 && address < 0x6000)
        banking_2bit = value & 3;
    else if (address >= 0x6000 && address < 0x8000)
        advanced_banking_mode = (value != 0);
    else if (address >= 0xa000 & address < 0xc000 && ram_banks.size())
    {
        uint8_t bank = (advanced_banking_mode ? banking_2bit : 0) & ram_mask;
        ram_banks[bank][address - 0xa000] = value;
    }
    else
    {
        std::cerr << "W: Writing to invalid memory region " << std::hex
            << address << std::dec << std::endl;
    }
}

const std::string& MBC1::getName() const
{
    return name;
}
