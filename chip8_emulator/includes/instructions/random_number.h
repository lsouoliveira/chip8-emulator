#ifndef RANDOM_NUMBER_H
#define RANDOM_NUMBER_H

#include <iostream>
#include <cstdlib>

#include <instructions/instruction.h>

namespace Chip8
{

class RandomNumber : public Instruction
{
private:
public:
    RandomNumber();
	virtual void Process(CPUState* state);
};

}

#endif /* ifndef RANDOM_NUMBER_H */
