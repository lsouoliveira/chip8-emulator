#include <instructions/random_number.h>

namespace Chip8
{

RandomNumber::RandomNumber()
{
}

void RandomNumber::Process(CPUState* state)
{	
    int targetRegister = (state->opcode & 0x0F00) >> 8;
    unsigned char constant = (state->opcode & 0x00FF);
    unsigned randomNumber = std::rand() % 256;

    state->v[targetRegister] = randomNumber & constant;
}

}
