#ifndef INSTRUCTION_MAP_H
#define INSTRUCTION_MAP_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>
#include <sstream>
#include <algorithm>
#include <cctype>

#include <cpu_state.h>
#include <instructions/instructions.h>

#define INSTRUCTION_NOT_FOUND(x) (std::cout << "Instruction not found 0x" << std::hex << std::to_string(x) << std::endl);
#define INSTRUCTION_NOT_IMPLEMENTED(x) (std::cout << "Instruction not implemented 0x" << std::hex << std::to_string(x) << std::endl);

namespace Chip8
{

class InstructionMap
{
public:
    static void PrintInstructionNotFound(unsigned short x);
    static void PrintInstructionNotImplemented(unsigned short x);
    static void Execute(CPUState* state);
};

}

#endif
