#include <instructions/sprite_location.h>

namespace Chip8
{

SpriteLocation::SpriteLocation()
{
}

void SpriteLocation::Process(CPUState* state)
{	
    int targetRegister = (state->opcode & 0x0F00) >> 8;

    state->i = state->v[targetRegister] * 5;
}

}
