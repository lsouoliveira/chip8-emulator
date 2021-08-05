#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <cpu_state.h>

namespace Chip8 
{

class Instruction {
private:
public:
	Instruction();
	virtual void Process(CPUState* state) = 0;
};

}

#endif
