#ifndef JUMP_H
#define JUMP_H

#include <instructions/instruction.h>

namespace Chip8
{

class Jump : public Instruction
{
private:
public:
    Jump();
	virtual void Process(CPUState* state);
};

}

#endif /* ifndef JUMP_H */
