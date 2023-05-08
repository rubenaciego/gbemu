#include "gameboy.hpp"
#include <iostream>
#include <cstring>

GameBoy::GameBoy() : model(DMG), cpu(this), mbc(nullptr)
{
    // Original model emulator for now
}

GameBoy::GameBoy(const ROM& rom) : GameBoy()
{
    loadROM(rom);
}

GameBoy::~GameBoy()
{
    if (mbc)
        delete mbc;
}

void GameBoy::reset()
{
    if (model == DMG || model == MGB)
    {
        write(0xff00, 0xcf);
        write(0xff01, 0x00);
        write(0xff02, 0x7e);
        write(0xff04, 0xab);
        write(0xff05, 0x00);
        write(0xff06, 0x00);
        write(0xff07, 0xf8);
        write(0xff0f, 0xe1);
        write(0xff10, 0x80);
        write(0xff11, 0xbf);
        write(0xff12, 0xf3);
        write(0xff13, 0xff);
        write(0xff14, 0xbf);
        write(0xff16, 0x3f);
        write(0xff18, 0x00);
        write(0xff19, 0xbf);
        write(0xff1a, 0x7f);
        write(0xff1b, 0xff);
        write(0xff1c, 0x9f);
        write(0xff1d, 0xff);
        write(0xff1e, 0xbf);
        write(0xff20, 0xff);
        write(0xff21, 0x00);
        write(0xff22, 0x00);
        write(0xff23, 0xbf);
        write(0xff24, 0x77);
        write(0xff25, 0xf3);
        write(0xff26, 0xf1);
        write(0xff40, 0x91);
        write(0xff41, 0x85);
        write(0xff42, 0x00);
        write(0xff43, 0x00);
        write(0xff44, 0x00);
        write(0xff45, 0x00);
        write(0xff46, 0xff);
        write(0xff47, 0xfc);
        write(0xff48, 0xff);
        write(0xff49, 0xff);
        write(0xff4a, 0x00);
        write(0xff4b, 0x00);
        write(0xff4d, 0xff);
        write(0xff4f, 0xff);
        write(0xff51, 0xff);
        write(0xff52, 0xff);
        write(0xff53, 0xff);
        write(0xff54, 0xff);
        write(0xff55, 0xff);
        write(0xff56, 0xff);
        write(0xff68, 0xff);
        write(0xff69, 0xff);
        write(0xff6a, 0xff);
        write(0xff6b, 0xff);
        write(0xff70, 0xff);
        write(0xffff, 0x00);
    }
    else
        throw std::runtime_error("GameBoy model not implemented");

    cpu.reset();
}

void GameBoy::loadROM(const ROM& rom)
{
    std::cout << "Loading ROM..." << std::endl;
    rom.printData();

    if (mbc)
        delete mbc;

    mbc = MBC::createMBC(rom);
    std::cout << "Using " << mbc->getName() << std::endl;

    reset();

    if (model == DMG)
    {
        cpu.f.h = cpu.f.c = (rom.header_checksum != 0);
    }
}

uint8_t GameBoy::read(uint16_t address) const
{
    if (address < 0x8000)
        return mbc->read(address);
    else if (address < 0xA000)
        return vram[address - 0x8000];
    else if (address < 0xC000)
        return mbc->read(address);
    else if (address < 0xE000)
        return wram[address - 0xC000];
    else if (address < 0xFE00)
        return read(address - 0x2000);
    else if (address < 0xFEA0)
        return 0; // OAM
    else if (address < 0xFF00)
        return 0; // Not usable
    else if (address < 0xFF80)
        return 0; // I/O registers
    else if (address < 0xFFFF)
        return hram[address - 0xFF80];
    else
        return ie;
}

void GameBoy::write(uint16_t address, uint8_t value)
{
    if (address < 0x8000)
        mbc->write(address, value);
    else if (address < 0xA000)
        vram[address - 0x8000] = value;
    else if (address < 0xC000)
        mbc->write(address, value);
    else if (address < 0xE000)
        wram[address - 0xC000] = value;
    else if (address < 0xFE00)
        write(address - 0x2000, value);
    else if (address < 0xFEA0)
        return; // OAM
    else if (address < 0xFF00)
        return; // Not usable
    else if (address < 0xFF80)
        return; // I/O registers
    else if (address < 0xFFFF)
        hram[address - 0xFF80] = value;
    else
        ie = value;
}

void GameBoy::tick()
{
    cpu.execute();
}

GameBoy::GBModel GameBoy::getModel() const
{
    return model;
}
