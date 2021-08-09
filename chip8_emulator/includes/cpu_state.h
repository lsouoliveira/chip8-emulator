#ifndef CPU_STATE_H
#define CPU_STATE_H

#include <iostream>

#include <constants.h>
#include <video.h>

namespace Chip8
{

struct CPUState {
    unsigned short opcode;
   	unsigned char* memory;
    unsigned char* v;
    unsigned short i;
    unsigned short pc;
    unsigned char delayTimer;
    unsigned char soundTimer;
    unsigned short* stack;
    unsigned short sp;
    unsigned char* key;
	double updateCounter;
	Video* video;

	CPUState()
	{
		memory = new unsigned char[MEMORY_SIZE];
		v = new unsigned char[NUM_REGISTERS]; 
		stack = new unsigned short[STACK_SIZE];
		key = new unsigned char[NUM_KEYS];
	}

	~CPUState()
	{
		delete[] memory;
		delete[] v;
		delete[] stack;
		delete[] key;
	}

	std::string ToString()
	{
		std::string result = "";

		for (int i = 0; i < NUM_REGISTERS; ++i) {
            result += "V" + std::to_string(i) + "=" + std::to_string(v[i]) + " / ";
		}

        result = result + "I=" + std::to_string(i);

		return result;
	}
};

}

#endif
