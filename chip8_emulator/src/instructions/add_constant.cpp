#include <instructions/add_constant.h>

namespace Chip8
{

AddConstant::AddConstant()
{
}

void AddConstant::Process(CPUState* state)
{	
    int targetRegister = (state->opcode & 0x0F00) >> 8;
    int constant = state->opcode & 0x00FF;

    state->v[targetRegister] += constant;
}

}
