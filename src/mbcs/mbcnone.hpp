#pragma once

#include "mbc.hpp"

class MBCNone : public MBC
{
public:
    MBCNone(const ROM& rom);

    virtual uint8_t read(uint16_t address) const override;
    virtual void write(uint16_t address, uint8_t value) override;

    virtual const std::string& getName() const override;

private:
    uint8_t rom[ROM_BANK_SIZE * 2];
    uint8_t ram[RAM_BANK_SIZE];

    const std::string name = "MBC None";
};
