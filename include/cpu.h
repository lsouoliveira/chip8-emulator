#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <functional>
#include <unordered_map>

#include <spdlog/spdlog.h>

#include <constants.h>
#include <video.h>

#include <instructions/instruction_map.h>
#include <instructions/clear_screen_instruction.h>

class Instruction;

namespace Chip8 {

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
};

class CPU {
private:
	CPUState state_;
    Video* video_;
	InstructionMap* instruction_map_;
	
	void FetchOpcode();
	void EmulateInstruction();
public:
    CPU(Video* video);
	~CPU();
    void Init();
    void EmulateCycles(int numCycles);
	void Update(double deltaTime);
	void UpdateTimers();
	void Load(const std::vector<unsigned char>& buffer);
};

}

#endif /* CPU_H */
