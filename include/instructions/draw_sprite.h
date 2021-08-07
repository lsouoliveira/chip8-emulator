#ifndef DRAW_SPRITE_H
#define DRAW_SPRITE_H
#include <instructions/instruction.h>

namespace Chip8
{

class DrawSprite : public Instruction
{
private:
public:
	DrawSprite();
	virtual void Process(CPUState* state);
};

}

#endif /* ifndef DRAW_SPRITE_H */
