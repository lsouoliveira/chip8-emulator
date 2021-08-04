#ifndef CLEAR_SCREEN_INSTRUCTION_H
#define CLEAR_SCREEN_INSTRUCTION_H

#include <instructions/instruction.h>

namespace Chip8
{
class ClearScreenInstruction : public Instruction
{
private:
public:
	ClearScreenInstruction();
	virtual void Process(CPUState* state);
};

}

#endif
