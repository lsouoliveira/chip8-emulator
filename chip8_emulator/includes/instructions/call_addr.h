#ifndef CALL_ADDR_H
#define CALL_ADDR_H

#include <instructions/instruction.h>

namespace Chip8
{

class CallAddr : public Instruction
{
private:
public:
    CallAddr();
	virtual void Process(CPUState* state);
};

}

#endif /* ifndef CALL_ADDR_H */
