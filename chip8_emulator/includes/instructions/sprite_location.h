#ifndef SPRITE_LOCATION_H
#define SPRITE_LOCATION_H

#include <instructions/instruction.h>

namespace Chip8
{

class SpriteLocation : public Instruction
{
private:
public:
    SpriteLocation();
	virtual void Process(CPUState* state);
};

}

#endif /* ifndef SPRITE_LOCATION_H */
