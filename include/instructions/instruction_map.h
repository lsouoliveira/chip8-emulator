#ifndef INSTRUCTION_MAP_H
#define INSTRUCTION_MAP_H

#include <iostream>
#include <vector>
#include <unordered_map>

#include <instructions/instruction.h>

namespace Chip8
{

class InstructionMap
{
private:
	std::unordered_map<unsigned short, Instruction*> map_;
	std::vector<unsigned short> search_masks_;
public:
	InstructionMap(std::vector<unsigned short> searchMasks);
	~InstructionMap();
	void Add(unsigned short opcode, Instruction* instruction);
	Instruction* Get(const unsigned short &opcode);
};

}

#endif
