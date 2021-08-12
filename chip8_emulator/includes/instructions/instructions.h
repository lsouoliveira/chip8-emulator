#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <iostream>
#include <cstdlib>

#include <cpu_state.h>

namespace Chip8 
{

class Instructions {
private:
    static unsigned short ExtractVx(unsigned short opcode);
    static unsigned short ExtractVy(unsigned short opcode);
    static unsigned short ExtractConstant(unsigned short opcode, unsigned char size);
public:
    static void ADD_7xkk(CPUState* state);
    static void AND_8xy2(CPUState* state);
    static void LD_fx33(CPUState* state);
    static void CALL(CPUState* state);
    static void CLS(CPUState* state);
    static void DRW_dxyn(CPUState* state);
    static void JP(CPUState* state);
    static void LD_annn(CPUState* state);
    static void LD_6xkk(CPUState* state);
    static void LD_fx07(CPUState* state);
    static void RND_cxkk(CPUState* state);
    static void LD_fx65(CPUState* state);
    static void RET(CPUState* state);
    static void LD_fx15(CPUState* state);
    static void SE_3xkk(CPUState* state);
    static void SKNP_exa1(CPUState* state);
    static void LD_fx29(CPUState* state);
    static void LD_8xy0(CPUState* state);
    static void SNE_4xkk(CPUState* state);
    static void LD_fx18(CPUState* state);
    static void ADD_8xy4(CPUState* state);
    static void SUB_8xy5(CPUState* state);
};

}

#endif
