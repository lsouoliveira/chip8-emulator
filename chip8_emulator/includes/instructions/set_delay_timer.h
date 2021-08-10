#ifndef SET_DELAY_TIMER_H
#define SET_DELAY_TIMER_H

#include <instructions/instruction.h>

namespace Chip8
{

class SetDelayTimer : public Instruction
{
private:
public:
    SetDelayTimer();
	virtual void Process(CPUState* state);
};

}

#endif /* ifndef SET_DELAY_TIMER_H */
