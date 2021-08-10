#ifndef MOVE_DELAY_TIMER_H
#define MOVE_DELAY_TIMER_H

#include <instructions/instruction.h>

namespace Chip8
{

class MoveDelayTimer : public Instruction
{
private:
public:
    MoveDelayTimer();
	virtual void Process(CPUState* state);
};

}

#endif /* ifndef MOVE_DELAY_TIMER_H */
