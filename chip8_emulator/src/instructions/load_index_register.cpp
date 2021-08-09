#include <instructions/load_index_register.h>

namespace Chip8
{

LoadIndexRegister::LoadIndexRegister()
{
}

void LoadIndexRegister::Process(CPUState* state)
{	
	int constant;

	constant = state->opcode & 0x0FFF;

	state->i = constant;
}

}
