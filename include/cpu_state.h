#ifndef CPU_STATE_H
#define CPU_STATE_H

#include <iostream>

#include <constants.h>
#include <video.h>

namespace Chip8
{

struct CPUState {
    unsigned short opcode;
    unsigned char memory[MEMORY_SIZE];
    unsigned char v[NUM_REGISTERS];
    unsigned short i;
    unsigned short pc;
    unsigned char delayTimer;
    unsigned char soundTimer;
    unsigned short stack[STACK_SIZE];
    unsigned short sp;
    unsigned char key[NUM_KEYS];
	double updateCounter;
	Video* video;

	std::string ToString()
	{
		std::string result = "";

		for (int i = 0; i < NUM_REGISTERS; ++i) {
			result += "v" + std::to_string(i) + " = " + std::to_string(v[i]) + "\n";
		}

		result = result + "\n" + "i = " + std::to_string(i) + "\n";
	
		return result;
	}
};

}

#endif
