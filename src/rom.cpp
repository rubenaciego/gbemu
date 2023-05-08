#include "rom.hpp"
#include <fstream>
#include <iterator>
#include <iostream>
#include <cstring>

ROM::ROM(const std::string& filepath)
{
    std::ifstream file;
    file.open(filepath, std::ios::in | std::ios::binary);

    if (!file.is_open())
        throw std::runtime_error("Error opening the file!");

    rom = std::vector<uint8_t>(std::istreambuf_iterator<char>(file), {});
    file.close();

    updateRomData();
}

void ROM::updateRomData()
{
    uint8_t cgb_flag = rom[0x0143];

    cgb = (cgb_flag == 0x80);
    cgb_only = (cgb_flag == 0xC0);

    if (cgb)
    {
        title[11] = 0;
        memcpy(title, &rom[0x0134], 11);
    }
    else
    {
        title[17] = 0;
        memcpy(title, &rom[0x0134], 16);
    }

    sgb = (rom[0x0146] == 0x03);
    cartridge = rom[0x0147];

    uint8_t romsize = rom[0x0148];

    if (romsize == 0x52)
        rom_banks = 72;
    else if (romsize == 0x53)
        rom_banks = 80;
    else if (romsize == 0x54)
        rom_banks = 96;
    else
        rom_banks = (1 << (romsize + 1));

    uint8_t ramsize = rom[0x0149];

    switch (ramsize)
    {
        case 2: ram_banks = 1; break;
        case 3: ram_banks = 4; break;
        case 4: ram_banks = 16; break;
        case 5: ram_banks = 8; break;
        default: ram_banks = 0;
    }

    license_code_old = rom[0x014b];
    license_code[0] = rom[0x0144];
    license_code[1] = rom[0x0145];

    japanese = !rom[0x014a];
    version = rom[0x014c];

    header_checksum = rom[0x014d];
    global_checksum = rom[0x014e] | (rom[0x014f] << 8);
}

void ROM::printData() const
{
    std::cout << "Title: " << title << std::endl;

    if (cgb)
    {
        if (cgb_only)
            std::cout << "CGB only game" << std::endl;
        else
            std::cout << "CGB compatible game" << std::endl;
    }
    else
        std::cout << "Non CGB game" << std::endl;

    std::cout << "License code: ";

    if (license_code_old == 0x33)
        std::cout << license_code[0] << license_code[1] << std::endl;
    else std::cout << "0x" << std::hex << (int)license_code_old << std::dec << std::endl;

    if (sgb)
        std::cout << "SGB compatible game" << std::endl;
    else
        std::cout << "Non SGB compatible game" << std::endl;

    std::cout << "Cartridge type: 0x" << std::hex << (int)cartridge << std::dec << std::endl;
    std::cout << "ROM banks: " << (int)rom_banks << std::endl;
    std::cout << "RAM banks: " << (int)ram_banks << std::endl;

    if (!japanese)
        std::cout << "Non ";
    std:: cout << "Japanese game" << std::endl;

    std::cout << "Version: " << (int)version << std::endl;

    std::cout << "Header checksum: " << (int)header_checksum << std::endl;
    std::cout << "Global checksum: " << (int)global_checksum << std::endl;
}
