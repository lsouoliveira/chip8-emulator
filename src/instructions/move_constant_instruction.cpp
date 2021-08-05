#include <instructions/move_constant_instruction.h>

namespace Chip8
{

MoveConstantInstruction::MoveConstantInstruction()
{
}

void MoveConstantInstruction::Process(CPUState* state)
{	
	int targetRegister;
	int constant;

	targetRegister = (state->opcode & 0x0F00) >> 8;
	constant = state->opcode & 0x00FF;

	state->v[targetRegister] = constant;
}

}
