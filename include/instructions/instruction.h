#ifndef INSTRUCTION_H
#define INSTRUCTION_H

namespace Chip8 
{

struct CPUState;
class Instruction {
private:
public:
	Instruction();
	virtual void Process(CPUState* state) = 0;
};

}

#endif
