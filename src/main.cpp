#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <ctime>

#include <chip8_emulator.h>
#include <utils.h>

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;
using namespace Chip8;

double getTime()
{
	return std::chrono::duration<double, std::milli>(system_clock::now().time_since_epoch()).count();
}

int main() {
	std::vector<unsigned char> romData = ReadData("roms/Pong (1 player).ch8");
	
	Chip8Emulator* chip8Emulator = new Chip8Emulator();
	chip8Emulator->Init();
	chip8Emulator->Load(romData);
	
	double lastTimestamp = getTime();

	while(true) {
		double currTime = getTime();
		double deltaTime = currTime - lastTimestamp;
		lastTimestamp = currTime;
		
		chip8Emulator->Update(deltaTime);
	}

	delete chip8Emulator;

    return 0;
}

