#ifndef READ_SEQUENCE_H
#define READ_SEQUENCE_H

#include <instructions/instruction.h>

namespace Chip8
{

class ReadSequence : public Instruction
{
private:
public:
    ReadSequence();
	virtual void Process(CPUState* state);
};

}

#endif /* ifndef READ_SEQUENCE_H */
