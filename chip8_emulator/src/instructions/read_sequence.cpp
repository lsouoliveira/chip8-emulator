#include <instructions/read_sequence.h>

namespace Chip8
{

ReadSequence::ReadSequence()
{
}

void ReadSequence::Process(CPUState* state)
{	
    int targetRegister = (state->opcode & 0x0F00) >> 8;

    for(int i = 0; i <= targetRegister; i++) {
        state->v[i] = state->memory[state->i + i];
    }
}

}
