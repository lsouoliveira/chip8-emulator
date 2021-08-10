#ifndef BCD_H
#define BCD_H

#include <iostream>
#include <instructions/instruction.h>

namespace Chip8
{

class Bcd : public Instruction
{
private:
public:
    Bcd();
	virtual void Process(CPUState* state);
};

}

#endif /* ifndef BCD_H */
