#pragma once

#include "mbc.hpp"
#include <vector>
#include <array>

class MBC1 : public MBC
{
public:
    MBC1(const ROM& rom);

    virtual uint8_t read(uint16_t address) const override;
    virtual void write(uint16_t address, uint8_t value) override;

    virtual const std::string& getName() const override;

private:
    std::vector<std::array<uint8_t, ROM_BANK_SIZE>> rom_banks;
    std::vector<std::array<uint8_t, RAM_BANK_SIZE>> ram_banks;

    bool battery;
    bool advanced_banking_mode;
    bool ram_enable;
    uint8_t rom_bank_5bit;
    uint8_t banking_2bit;

    const std::string name = "MBC1";
};
