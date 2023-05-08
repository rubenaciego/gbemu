#pragma once

#include "core.hpp"
#include <string>
#include <vector>

class ROM
{
public:
    ROM(const std::string& filepath);
    
    void updateRomData();
    void printData() const;

    char title[17];
    bool cgb;
    bool cgb_only;
    uint8_t license_code_old;
    char license_code[2];
    bool sgb;
    uint8_t cartridge;
    uint16_t rom_banks;
    uint8_t ram_banks;
    bool japanese;
    uint8_t version;
    uint8_t header_checksum;
    uint16_t global_checksum;

    std::vector<uint8_t> rom;
};
