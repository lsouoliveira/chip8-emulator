#ifndef RET_H
#define RET_H

#include <instructions/instruction.h>

namespace Chip8
{

class Ret : public Instruction
{
private:
public:
    Ret();
	virtual void Process(CPUState* state);
};

}

#endif /* ifndef RET_H */
