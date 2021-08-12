#include <instructions/instructions.h>

namespace Chip8
{
    unsigned short Instructions::ExtractVx(unsigned short opcode)
    {
        return (opcode & 0x0F00) >> 8;
    }

    unsigned short Instructions::ExtractVy(unsigned short opcode)
    {
        return (opcode & 0x00F0) >> 4;
    }

    unsigned short Instructions::ExtractConstant(unsigned short opcode, unsigned char size)
    {
        unsigned short mask = 0;

        for(int i = 0; i < size; i++) {
            mask = (mask << 4) + 0xF;
        }

        return opcode & mask;
    }

    void Instructions::ADD_7xkk(CPUState* state){
        unsigned short vx = ExtractVx(state->opcode);
        unsigned short k = ExtractConstant(state->opcode, 3);

        state->v[vx] += k;
    }

    void Instructions::AND_8xy2(CPUState* state){
        unsigned short vx = ExtractVx(state->opcode);
        unsigned short vy = ExtractVy(state->opcode);

        state->v[vx] = state->v[vx] & state->v[vy];
    }

    void Instructions::LD_fx33(CPUState* state){
        int targetV = (state->opcode & 0x0F00) >> 8;
        std::string targetNumber = std::to_string(state->v[targetV]);

        while(targetNumber.size() < 3) {
            targetNumber = "0" + targetNumber;
        }

        state->memory[state->i] = targetNumber[0] - '0';
        state->memory[state->i + 1] = targetNumber[1] - '0';
        state->memory[state->i + 2] = targetNumber[2] - '0';
    }

    void Instructions::CALL(CPUState* state){
        unsigned short k = ExtractConstant(state->opcode, 3);

        state->stack[state->sp] = state->pc;
        state->sp++;
        state->pc = k;
    }

    void Instructions::CLS(CPUState* state){
        state->video->ClearBuffer();
    }

    void Instructions::DRW_dxyn(CPUState* state){
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

            if(x < 0) {
                x = 64 - 8;
            }

            if(x >= 64) {
                x = 0;
            }

            if(y < 0) {
                y = 32 - 8;
            }

            if(y >= 32) {
                y = 0;
            }

            state->v[0xF] = 0;

            for (int i = 0; i < spriteHeight; ++i) {
                unsigned char spriteLine = state->memory[state->i + i];

                for(int j = 0; j < 8; j++) {
                    int videoX = (x + j);
                    int videoY = (y + i);

                    if(videoX >= 64 || videoY >= 32 || videoX < 0 || videoY < 0) {
                        continue;
                    }

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

    void Instructions::JP(CPUState* state){
        unsigned short k = ExtractConstant(state->opcode, 3);
        state->pc = k;
    }

    void Instructions::LD_annn(CPUState* state){
        unsigned short k = ExtractConstant(state->opcode, 3);
        state->i = k;
    }

    void Instructions::LD_6xkk(CPUState* state){
        unsigned short vx = ExtractVx(state->opcode);
        unsigned short k = ExtractConstant(state->opcode, 2);

        state->v[vx] = k;
    }

    void Instructions::LD_fx07(CPUState* state){
        unsigned short vx = ExtractVx(state->opcode);

        state->v[vx] = state->delayTimer;
    }

    void Instructions::RND_cxkk(CPUState* state){
        unsigned short vx = ExtractVx(state->opcode);
        unsigned short k = ExtractConstant(state->opcode, 2);
        unsigned short randomNumber = std::rand() % 256;

        state->v[vx] = randomNumber & k;
    }

    void Instructions::LD_fx65(CPUState* state){
        int targetRegister = (state->opcode & 0x0F00) >> 8;

            for(int i = 0; i <= targetRegister; i++) {
                state->v[i] = state->memory[state->i + i];
            }
    }

    void Instructions::RET(CPUState* state){
        state->sp -= 1;
            state->pc = state->stack[state->sp];
    }

    void Instructions::LD_fx15(CPUState* state){
        unsigned short vx = ExtractVx(state->opcode);

        state->delayTimer = state->v[vx];
    }

    void Instructions::SE_3xkk(CPUState* state){
        unsigned short vx = ExtractVx(state->opcode);
        unsigned short k = ExtractConstant(state->opcode, 2);

        if(state->v[vx] == k) {
            state->pc += 2;
        }
    }

    void Instructions::SKNP_exa1(CPUState* state) {
        unsigned short vx = ExtractVx(state->opcode);

        if(state->key[state->v[vx]] == 0) {
            state->pc += 2;
        }
    }

    void Instructions::LD_fx29(CPUState* state){
        unsigned short vx = ExtractVx(state->opcode);

        state->i = state->v[vx] * 5;
    }

    void Instructions::LD_8xy0(CPUState *state)
    {
        unsigned short vx = ExtractVx(state->opcode);
        unsigned short vy = ExtractVy(state->opcode);

        state->v[vx] = state->v[vy];
    }

    void Instructions::SNE_4xkk(CPUState *state)
    {
        unsigned short vx = ExtractVx(state->opcode);
        unsigned short k = ExtractConstant(state->opcode, 2);

        if(state->v[vx] != k) {
            state->pc += 2;
        }
    }

    void Instructions::LD_fx18(CPUState *state)
    {
        unsigned short vx = ExtractVx(state->opcode);
        state->soundTimer = state->v[vx];
    }

    void Instructions::ADD_8xy4(CPUState *state)
    {
       unsigned short vx = ExtractVx(state->opcode);
       unsigned short vy = ExtractVy(state->opcode);
       unsigned short sum = state->v[vx] + state->v[vy];

       state->v[vx] = sum & 0x00FF;
       state->v[0xF] = (sum >> 8) & 1;
    }

    void Instructions::SUB_8xy5(CPUState *state)
    {
       unsigned short vx = ExtractVx(state->opcode);
       unsigned short vy = ExtractVy(state->opcode);
       unsigned short sub = state->v[vx] - state->v[vy];

       state->v[0xF] = (state->v[vx] > state->v[vy] ? 1 : 0);
       state->v[vx] = sub & 0x00FF;
    }

}
