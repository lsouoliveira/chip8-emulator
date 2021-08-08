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
#include <cpu_state.h>
#include <instructions/instruction_map.h>
#include <instructions/clear_screen_instruction.h>
#include <instructions/move_constant_instruction.h>
#include <instructions/load_index_register.h>
#include <instructions/draw_sprite.h>

class Instruction;

namespace Chip8 {

class CPU {
private:
	CPUState state_;
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
