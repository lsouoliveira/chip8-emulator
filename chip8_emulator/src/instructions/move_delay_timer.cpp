#include <instructions/move_delay_timer.h>

namespace Chip8
{

MoveDelayTimer::MoveDelayTimer()
{
}

void MoveDelayTimer::Process(CPUState* state)
{	
    int targetRegister = (state->opcode & 0x0F00) >> 8;

    state->v[targetRegister] = state->delayTimer;
}

}
