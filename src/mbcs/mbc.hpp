#pragma once

#include "core.hpp"
#include "rom.hpp"

class MBC
{
public:
    virtual uint8_t read(uint16_t address) const = 0;
    virtual void write(uint16_t address, uint8_t value) = 0;
    virtual const std::string& getName() const = 0;

    static MBC* createMBC(const ROM& rom);
};
