#include <instructions/call_addr.h>

namespace Chip8
{

CallAddr::CallAddr()
{
}

void CallAddr::Process(CPUState* state)
{	
    unsigned short targetAddress = state->opcode & 0x0FFF;

    state->stack[state->sp] = state->pc;
    state->sp++;
    state->pc = targetAddress;
}

}
