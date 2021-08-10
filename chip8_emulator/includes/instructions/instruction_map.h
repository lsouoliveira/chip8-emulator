#ifndef INSTRUCTION_MAP_H
#define INSTRUCTION_MAP_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>

#include <cpu_state.h>

#define BIND_INSTRUCTION_CALLBACK(f) [](CPUState* state) { f(state); }
#define INSTRUCTION_CALLBACK std::function<void(CPUState*)>

namespace Chip8
{

class InstructionMap
{
private:
    std::unordered_map<unsigned short, INSTRUCTION_CALLBACK> map_;
	std::vector<unsigned short> search_masks_;
public:
	InstructionMap(std::vector<unsigned short> searchMasks);
	~InstructionMap();
    void Add(unsigned short opcode, std::function<void(CPUState*)>);
    INSTRUCTION_CALLBACK Get(const unsigned short &opcode);
};

}

#endif
