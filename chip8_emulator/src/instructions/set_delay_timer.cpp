#include <instructions/set_delay_timer.h>

namespace Chip8
{

SetDelayTimer::SetDelayTimer()
{
}

void SetDelayTimer::Process(CPUState* state)
{	
    int targetRegister = (state->opcode & 0x0F00) >> 8;

    state->delayTimer = state->v[targetRegister];
}

}
