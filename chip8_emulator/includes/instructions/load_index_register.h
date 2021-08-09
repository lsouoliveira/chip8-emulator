#ifndef LOAD_INDEX_REGISTER_H
#define LOAD_INDEX_REGISTER_H
#include <instructions/instruction.h>

namespace Chip8
{

class LoadIndexRegister : public Instruction
{
private:
public:
	LoadIndexRegister();
	virtual void Process(CPUState* state);
};

}

#endif /* ifndef LOAD_INDEX_REGISTER_H */
