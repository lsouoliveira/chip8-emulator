#include <instructions/jump.h>

namespace Chip8
{

Jump::Jump()
{
}

void Jump::Process(CPUState* state)
{	
    int constant = (state->opcode & 0x0FFF);
    state->pc = constant;
}

}
