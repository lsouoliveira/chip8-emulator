#include <instructions/instruction_map.h>

namespace Chip8
{

InstructionMap::InstructionMap(std::vector<unsigned short> searchMasks)
	: search_masks_(searchMasks)
{
}

InstructionMap::~InstructionMap()
{
}

void InstructionMap::Add(unsigned short opcode, INSTRUCTION_CALLBACK instruction)
{
	map_.insert(std::make_pair<>(opcode, instruction));
}

INSTRUCTION_CALLBACK InstructionMap::Get(const unsigned short& opcode)
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
