#include <iostream>
#include <vector>
#include <fstream>
#include <chip8_emulator.h>
#include <utils.h>

using namespace Chip8;

int main() {
	std::vector<unsigned char> romData = ReadData("roms/Pong (1 player).ch8");
	
	Chip8Emulator* chip8Emulator = new Chip8Emulator();
	chip8Emulator->Load(romData);

	delete chip8Emulator;

    return 0;
}

