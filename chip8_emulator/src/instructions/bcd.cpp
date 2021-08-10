#include <instructions/bcd.h>

namespace Chip8
{

Bcd::Bcd()
{
}

void Bcd::Process(CPUState* state)
{	
    int targetV = (state->opcode & 0x0F00) >> 8;
    std::string targetNumber = std::to_string(state->v[targetV]);

    while(targetNumber.size() < 3) {
        targetNumber = "0" + targetNumber;
    }

    state->memory[state->i] = targetNumber[0] - '0';
    state->memory[state->i + 1] = targetNumber[1] - '0';
    state->memory[state->i + 2] = targetNumber[2] - '0';
}

}
