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
    static unsigned short ExtractConstant(unsigned short opcode, unsigned char size);
public:
    static void AddConstant(CPUState* state);
    static void AndRegister(CPUState* state);
    static void Bcd(CPUState* state);
    static void CallAddr(CPUState* state);
    static void ClearScreen(CPUState* state);
    static void DrawSprite(CPUState* state);
    static void Jump(CPUState* state);
    static void LoadIndexRegister(CPUState* state);
    static void LoadRegisterWithConstant(CPUState* state);
    static void MoveDelayTimer(CPUState* state);
    static void RandomNumber(CPUState* state);
    static void ReadSequenceIntoRegisters(CPUState* state);
    static void Ret(CPUState* state);
    static void SetDelayTimer(CPUState* state);
    static void SkipIfEqual(CPUState* state);
    static void SkipIfKeyNotPressed(CPUState* state);
    static void FontSpriteLocation(CPUState* state);
    static void StoreRegister(CPUState* state);
    static void SNE_4xkk(CPUState* state);
};

}

#endif
