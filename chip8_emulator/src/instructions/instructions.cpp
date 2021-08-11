#include <instructions/instructions.h>

namespace Chip8
{
    unsigned short Instructions::ExtractVx(unsigned short opcode)
    {
        return (opcode & 0x0F00) >> 8;
    }

    unsigned short Instructions::ExtractConstant(unsigned short opcode, unsigned char size)
    {
        unsigned short mask = 0;

        for(int i = 0; i < size; i++) {
            mask = (mask << 4) + 0xF;
        }

        return opcode & mask;
    }

    void Instructions::AddConstant(CPUState* state){
        int targetRegister = (state->opcode & 0x0F00) >> 8;
        int constant = state->opcode & 0x00FF;

        state->v[targetRegister] += constant;
    }

    void Instructions::AndRegister(CPUState* state){
        int targetRegisterA = (state->opcode & 0x0F00) >> 8;
        int targetRegisterB = (state->opcode & 0x00F0) >> 4;

        state->v[targetRegisterA] = state->v[targetRegisterA] & state->v[targetRegisterB];
    }

    void Instructions::Bcd(CPUState* state){
        int targetV = (state->opcode & 0x0F00) >> 8;
        std::string targetNumber = std::to_string(state->v[targetV]);

        while(targetNumber.size() < 3) {
            targetNumber = "0" + targetNumber;
        }

        state->memory[state->i] = targetNumber[0] - '0';
        state->memory[state->i + 1] = targetNumber[1] - '0';
        state->memory[state->i + 2] = targetNumber[2] - '0';
    }

    void Instructions::CallAddr(CPUState* state){
        unsigned short targetAddress = state->opcode & 0x0FFF;

            state->stack[state->sp] = state->pc;
            state->sp++;
            state->pc = targetAddress;
    }

    void Instructions::ClearScreen(CPUState* state){
        state->video->ClearBuffer();
    }

    void Instructions::DrawSprite(CPUState* state){
        unsigned char vx;
            unsigned char vy;
            unsigned char spriteHeight;
            int x;
            int y;

            vx = ((state->opcode) & 0x0F00) >> 8;
            vy = ((state->opcode) & 0x00F0) >> 4;
            spriteHeight = (state->opcode) & 0x000F;

            x = state->v[vx];
            y = state->v[vy];



            for (int i = 0; i < spriteHeight; ++i) {
                unsigned char spriteLine = state->memory[state->i + i];

                for(int j = 0; j < 8; j++) {
                    int videoX = (x + j) % 64;
                    int videoY = (y + i) % 32;
                    int pixelPos = 64 * (videoY) + videoX;
                    unsigned char pixelColor = ((spriteLine >> (7 - j)) & 1);
                    unsigned char currPixelColor = state->video->GetBuffer()[pixelPos];
                    unsigned char updatedColor = (currPixelColor + pixelColor) % 2;

                    if(pixelColor == 1 && updatedColor == 0) {
                        state->v[0xF] = 1;
                    }

                    state->video->GetBuffer()[pixelPos] = updatedColor;
                }
            }
    }

    void Instructions::Jump(CPUState* state){
        int constant = (state->opcode & 0x0FFF);
        state->pc = constant;
    }

    void Instructions::LoadIndexRegister(CPUState* state){
        int constant;
        constant = state->opcode & 0x0FFF;
        state->i = constant;
    }

    void Instructions::LoadRegisterWithConstant(CPUState* state){
        int targetRegister;
            int constant;

            targetRegister = (state->opcode & 0x0F00) >> 8;
            constant = state->opcode & 0x00FF;

            state->v[targetRegister] = constant;
    }

    void Instructions::MoveDelayTimer(CPUState* state){
        int targetRegister = (state->opcode & 0x0F00) >> 8;

            state->v[targetRegister] = state->delayTimer;
    }

    void Instructions::RandomNumber(CPUState* state){
        int targetRegister = (state->opcode & 0x0F00) >> 8;
            unsigned char constant = (state->opcode & 0x00FF);
            unsigned randomNumber = std::rand() % 256;

            state->v[targetRegister] = randomNumber & constant;
    }

    void Instructions::ReadSequenceIntoRegisters(CPUState* state){
        int targetRegister = (state->opcode & 0x0F00) >> 8;

            for(int i = 0; i <= targetRegister; i++) {
                state->v[i] = state->memory[state->i + i];
            }
    }

    void Instructions::Ret(CPUState* state){
        state->sp -= 1;
            state->pc = state->stack[state->sp];
    }

    void Instructions::SetDelayTimer(CPUState* state){
        int targetRegister = (state->opcode & 0x0F00) >> 8;

        state->delayTimer = state->v[targetRegister];
    }

    void Instructions::SkipIfEqual(CPUState* state){
        int targetRegister = (state->opcode & 0x0F00) >> 8;
            int constant = (state->opcode & 0x00FF);

            if(state->v[targetRegister] == constant) {
                state->pc += 2;
            }
    }

    void Instructions::SkipIfKeyNotPressed(CPUState* state) {
        int targetRegister = (state->opcode & 0x0F00) >> 8;

        if(state->key[state->v[targetRegister]] == 0) {
            state->pc += 2;
        }
    }

    void Instructions::FontSpriteLocation(CPUState* state){
        int targetRegister = (state->opcode & 0x0F00) >> 8;

            state->i = state->v[targetRegister] * 5;
    }

    void Instructions::StoreRegister(CPUState *state)
    {
        int targetRegisterA = (state->opcode & 0x0F00) >> 8;
        int targetRegisterB = (state->opcode & 0x00F0) >> 4;

        state->v[targetRegisterA] = state->v[targetRegisterB];
    }

    void Instructions::SNE_4xkk(CPUState *state)
    {
        unsigned short vx = ExtractVx(state->opcode);
        unsigned short k = ExtractConstant(state->opcode, 2);

        if(state->v[vx] != k) {
            state->pc += 2;
        }
    }

}
