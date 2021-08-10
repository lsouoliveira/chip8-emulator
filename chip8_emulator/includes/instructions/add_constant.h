#ifndef ADD_CONSTANT_H
#define ADD_CONSTANT_H

#include <instructions/instruction.h>

namespace Chip8
{

class AddConstant : public Instruction
{
private:
public:
    AddConstant();
	virtual void Process(CPUState* state);
};

}

#endif /* ifndef ADD_CONSTANT_H */
