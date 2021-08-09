#ifndef MOVE_CONSTANT_INSTRUCTION_H
#define MOVE_CONSTANT_INSTRUCTION_H
#include <instructions/instruction.h>

namespace Chip8
{

class MoveConstantInstruction : public Instruction
{
private:
public:
	MoveConstantInstruction();
	virtual void Process(CPUState* state);
};

}

#endif /* ifndef MOVE_CONSTANT_INSTRUCTION_H */
