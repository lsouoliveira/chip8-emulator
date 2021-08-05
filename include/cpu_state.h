#ifndef CPU_STATE_H
#define CPU_STATE_H

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
};

}

#endif
