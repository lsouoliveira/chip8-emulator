#include <instructions/instruction_map.h>

namespace Chip8
{

void InstructionMap::PrintInstructionNotFound(unsigned short x)
{
    std::cout << "Instruction not found 0x" << std::hex << x << std::endl;
}

void InstructionMap::PrintInstructionNotImplemented(unsigned short x)
{

    std::cout << "Instruction not implemented 0x" << std::hex << x << std::endl;
}

void InstructionMap::Execute(CPUState* state)
{
    switch(state->opcode & 0xF000) {
        case 0x0000:
            switch(state->opcode & 0x00F0) {
                case 0x00C0:
                    PrintInstructionNotImplemented(state->opcode);
                    break;
                default:
                    switch(state->opcode & 0x00FF) {
                        case 0x00E0:
                            Instructions::CLS(state);
                            break;
                        case 0x00EE:
                            Instructions::RET(state);
                            break;
                        case 0x00FB:
                            PrintInstructionNotImplemented(state->opcode);
                            break;
                        case 0x00FC:
                            PrintInstructionNotImplemented(state->opcode);
                            break;
                        case 0x00FD:
                            PrintInstructionNotImplemented(state->opcode);
                            break;
                        case 0x00FE:
                            PrintInstructionNotImplemented(state->opcode);
                            break;
                        case 0x00FF:
                            PrintInstructionNotImplemented(state->opcode);
                            break;
                        case 0x0000:
                            PrintInstructionNotImplemented(state->opcode);
                            break;
                    }
            }
            break;
        case 0x1000:
            Instructions::JP(state);
            break;
        case 0x2000:
            Instructions::CALL(state);
            break;
        case 0x3000:
            Instructions::SE_3xkk(state);
            break;
        case 0x4000:
            Instructions::SNE_4xkk(state);
            break;
        case 0x5000:
            PrintInstructionNotImplemented(state->opcode);
            break;
        case 0x6000:
            Instructions::LD_6xkk(state);
            break;
        case 0x7000:
            Instructions::ADD_7xkk(state);
            break;
        case 0x8000:
            switch(state->opcode & 0x000F) {
                case 0x0000:
                    Instructions::LD_8xy0(state);
                    break;
                case 0x0001:
                    PrintInstructionNotImplemented(state->opcode);
                    break;
                case 0x0002:
                    Instructions::AND_8xy2(state);
                    break;
                case 0x0003:
                    PrintInstructionNotImplemented(state->opcode);
                    break;
                case 0x0004:
                    PrintInstructionNotImplemented(state->opcode);
                    break;
                case 0x0005:
                    PrintInstructionNotImplemented(state->opcode);
                    break;
                case 0x0006:
                    PrintInstructionNotImplemented(state->opcode);
                    break;
                case 0x0007:
                    PrintInstructionNotImplemented(state->opcode);
                    break;
                case 0x000E:
                    PrintInstructionNotImplemented(state->opcode);
                    break;
            }
            break;
        case 0xA000:
            Instructions::LD_annn(state);
            break;
        case 0xB000:
            PrintInstructionNotImplemented(state->opcode);
            break;
        case 0xC000:
            Instructions::RND_cxkk(state);
            break;
        case 0xD000:
            switch(state->opcode & 0x000F) {
                case 0x0000:
                    PrintInstructionNotImplemented(state->opcode);
                    break;
                default:
                    Instructions::DRW_dxyn(state);
            }
            break;
        case 0xE000:
            switch(state->opcode & 0x00FF) {
                case 0x009E:
                    PrintInstructionNotImplemented(state->opcode);
                    break;
                case 0x00A1:
                    Instructions::SKNP_exa1(state);
                    break;
            }
            break;
        case 0xF000:
            switch(state->opcode & 0x00FF) {
                case 0x0007:
                    Instructions::LD_fx07(state);
                    break;
                case 0x000A:
                    PrintInstructionNotImplemented(state->opcode);
                    break;
                case 0x0015:
                    Instructions::LD_fx15(state);
                    break;
                case 0x0018:
                    Instructions::LD_fx18(state);
                    break;
                case 0x001E:
                    PrintInstructionNotImplemented(state->opcode);
                    break;
                case 0x0029:
                    Instructions::LD_fx29(state);
                    break;
                case 0x0030:
                    PrintInstructionNotImplemented(state->opcode);
                    break;
                case 0x0033:
                    Instructions::LD_fx33(state);
                    break;
                case 0x0055:
                    PrintInstructionNotImplemented(state->opcode);
                    break;
                case 0x0065:
                    Instructions::LD_fx65(state);
                    break;
                case 0x0075:
                    PrintInstructionNotImplemented(state->opcode);
                    break;
                case 0x0085:
                    PrintInstructionNotImplemented(state->opcode);
                    break;
            }
            break;
        default:
            PrintInstructionNotImplemented(state->opcode);
    }
}

}

