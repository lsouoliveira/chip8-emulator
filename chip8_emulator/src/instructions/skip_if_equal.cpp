#include <instructions/skip_if_equal.h>

namespace Chip8
{

SkipIfEqual::SkipIfEqual()
{
}

void SkipIfEqual::Process(CPUState* state)
{	
    int targetRegister = (state->opcode & 0x0F00) >> 8;
    int constant = (state->opcode & 0x00FF);

    if(state->v[targetRegister] == constant) {
        state->pc += 2;
    }
}

}
