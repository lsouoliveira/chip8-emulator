#include <instructions/instruction_map.h>

namespace Chip8
{

InstructionMap::InstructionMap(std::vector<unsigned short> searchMasks)
	: search_masks_(searchMasks)
{
}

InstructionMap::~InstructionMap()
{
	for(auto it = map_.begin(); it != map_.end(); ++it) {
		delete (it->second);
	}
}

void InstructionMap::Add(unsigned short opcode, Instruction* instruction)
{
	map_.insert(std::make_pair<>(opcode, instruction));
}

Instruction* InstructionMap::Get(const unsigned short& opcode)
{
	for(auto searchMask : search_masks_) {
		auto searchResult = map_.find(opcode & searchMask);

		if(searchResult != map_.end()) {
			return searchResult->second;
		}
	}

	return nullptr;
}

}
