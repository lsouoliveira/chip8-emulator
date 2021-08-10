#include <instructions/ret.h>

namespace Chip8
{

Ret::Ret()
{
}

void Ret::Process(CPUState* state)
{	
    state->sp -= 1;
    state->pc = state->stack[state->sp];
}

}
