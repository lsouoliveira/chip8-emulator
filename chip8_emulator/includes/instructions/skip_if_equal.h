#ifndef SKIP_IF_EQUAL_H
#define SKIP_IF_EQUAL_H

#include <instructions/instruction.h>

namespace Chip8
{

class SkipIfEqual : public Instruction
{
private:
public:
    SkipIfEqual();
	virtual void Process(CPUState* state);
};

}

#endif /* ifndef SKIP_IF_EQUAL_H */
