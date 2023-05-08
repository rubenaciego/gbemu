#include <iostream>
#include "gameboy.hpp"

using namespace std;

int main(int argc, const char* argv[])
{
    std::cout << "GameBoy emulator by rubenaciego" << std::endl << std::endl;

    std::string filepath(argv[1]);
    ROM rom(filepath);
    GameBoy gb(rom);

    while (true)
        gb.tick();

    return 0;
}
