#include <gtest/gtest.h>
#include <cpu_state.h>
#include <instructions/instructions.h>
#include <video.h>
#include <constants.h>

using namespace Chip8;

TEST(ADD_7xkkTest, ShouldAddConstantToRegister) {
    CPUState state;
    unsigned short opcode = 0x7055;

    state.v[0] = 20;
    state.opcode = opcode;

    Instructions::ADD_7xkk(&state);

    EXPECT_EQ(state.v[0], 20 + 0x55);
}

TEST(AND_8xy2Test, ShouldPerformBitwiseAndBetweenRegisters) {
    CPUState state;
    unsigned short opcode = 0x8012;
    unsigned char a = 228;
    unsigned char b = 176;

    state.opcode = opcode;

    state.v[0] = a;
    state.v[1] = b;

    Instructions::AND_8xy2(&state);

    EXPECT_EQ(state.v[0], a & b);
}

TEST(LD_fx33Test, ShouldSavePCInStackAndIncrementSP) {
    CPUState state;
    unsigned short opcode = 0xf033;

    state.opcode = opcode;
    state.v[0] = 123;
    state.i = 0x200;

    Instructions::LD_fx33(&state);

    EXPECT_EQ(state.memory[state.i], 1);
    EXPECT_EQ(state.memory[state.i + 1], 2);
    EXPECT_EQ(state.memory[state.i + 2], 3);
}


TEST(CALLTest, ShouldSavePCInStackAndIncrementSP) {
    CPUState state;
    unsigned short opcode = 0x2222;
    state.opcode = opcode;

    state.pc = 0x200;
    state.sp = 0;

    for (int i = 0; i < Chip8::STACK_SIZE; ++i) {
        state.stack[i] = 0;
    }

    state.pc += 2;

    Instructions::CALL(&state);

    EXPECT_EQ(state.sp, 1);
    EXPECT_EQ(state.stack[0], 0x202);
    EXPECT_EQ(state.pc, 0x222);
}

TEST(CLSTest, ShouldClearScreenBuffer) {
    CPUState state;
    Video video;
    state.video = &video;

    for (int i = 0; i < Chip8::VIDEO_BUFFER_SIZE; ++i) {
        state.video->GetBuffer()[i] = 1;
    }

    Instructions::CLS(&state);

    for (int i = 0; i < Chip8::VIDEO_BUFFER_SIZE; ++i) {
        EXPECT_EQ(state.video->GetBuffer()[i], 0);
    }
}

TEST(LD_annnTest, ShouldLoadRegisterIWithCorrectValue) {
    CPUState state;
    unsigned short opcode = 0xAFFF;

    state.opcode = opcode;
    state.i = 0;

    Instructions::LD_annn(&state);

    EXPECT_EQ(state.i, 0xFFF);
}

TEST(LD_6xkkTest, ShouldLoadRegisterWithCorrectValue) {
    CPUState state;
    unsigned short opcode = 0x64FF;

    state.opcode = opcode;
    for (int i = 0; i < 15; ++i) {
        state.v[i] = 0;
    }

    Instructions::LD_6xkk(&state);

    EXPECT_EQ(state.v[4], 0x00FF);
}

TEST(LD_fx07Test, ShouldMoveDelayTimerToRegister) {
    CPUState state;
    unsigned short opcode = 0x7007;
    state.opcode = opcode;

    state.delayTimer = 60;

    Instructions::LD_fx07(&state);

    EXPECT_EQ(state.v[0], 60);
}

TEST(LD_fx65Test, ShouldWriteAddressSequenceIntoRegisters) {
    CPUState state;
    unsigned short opcode = 0xf665;

    for(int i = 0; i < 15; i++) {
        state.v[i] = 0;
    }

    for(int i = 0; i <= 6; i++) {
        state.memory[0x200 + i] = i + 1;
    }

    state.i = 0x200;
    state.opcode = opcode;

    Instructions::LD_fx65(&state);

    for(int i = 0; i <= 6; i++) {
        EXPECT_EQ(state.v[i], i + 1);
    }
}

TEST(LD_fx15Test, ShouldSetDelayTimerToRegisterValue) {
    CPUState state;
    unsigned short opcode = 0x7015;

    state.v[0] = 20;
    state.opcode = opcode;

    Instructions::LD_fx15(&state);

    EXPECT_EQ(state.delayTimer, 20);
}

TEST(SE_3xkkTest, ShouldSkipNextInstructionIfVxEqualToKk) {
    CPUState state;
    unsigned short opcode = 0x3042;
    state.opcode = opcode;

    state.pc = 0;
    state.v[0] = 0x42;

    Instructions::SE_3xkk(&state);

    EXPECT_EQ(state.pc, 2);
}

TEST(SE_3xkkTest, ShouldNotSkipNextInstructionIfVxDifferentToKk) {
    CPUState state;
    unsigned short opcode = 0x3044;
    state.opcode = opcode;

    state.pc = 0;
    state.v[0] = 0x42;

    Instructions::SE_3xkk(&state);

    EXPECT_EQ(state.pc, 0);
}

TEST(SKNP_exa1Test, ShouldSkipNextInstructionIfKeyNotPressed) {
    CPUState state;
    unsigned short opcode = 0xe0a1;
    unsigned short pc;

    state.opcode = opcode;
    state.pc = 0x200;
    state.v[0] = 0;
    state.key[0] = 0;
    pc = state.pc + 2;

    Instructions::SKNP_exa1(&state);

    EXPECT_EQ(state.pc, pc);
}

TEST(SKNP_exa1Test, ShouldNotSkipNextInstructionIfKeyIsPressed) {
    CPUState state;
    unsigned short opcode = 0xe0a1;
    unsigned short pc;

    state.pc = 0x200;
    state.opcode = opcode;
    state.v[0] = 0;
    state.key[0] = 1;
    pc = state.pc;

    Instructions::SKNP_exa1(&state);

    EXPECT_EQ(state.pc, pc);
}

TEST(LD_fx29Test, ShouldPointToFontSpriteLocation) {
    CPUState state;
    unsigned short opcode = 0xf029;

    state.opcode = opcode;
    state.v[0] = 0xC;

    Instructions::LD_fx29(&state);

    EXPECT_EQ(state.i, 0xC * 5);
}

TEST(LD_8xy0Test, ShouldStoreVyInVx) {
    CPUState state;
    unsigned short opcode = 0x8010;

    state.opcode = opcode;
    state.v[0] = 1;
    state.v[1] = 2;

    Instructions::LD_8xy0(&state);

    EXPECT_EQ(state.v[0], state.v[1]);
}

TEST(SNE_4xkkTest, ShouldSkipNextInstructionIfVxIsDifferentThanKk) {
    CPUState state;
    unsigned short opcode = 0x4000;
    unsigned short pc;

    state.opcode = opcode;
    state.pc = 0x200;
    state.v[0] = 1;
    pc = state.pc;

    Instructions::SNE_4xkk(&state);

    EXPECT_EQ(state.pc, pc + 2);
}

TEST(SNE_4xkkTest, ShouldNotSkipNextInstructionIfVxIsEqualToKk) {
    CPUState state;
    unsigned short opcode = 0x4000;
    unsigned short pc;

    state.opcode = opcode;
    state.pc = 0x200;
    state.v[0] = 0;
    pc = state.pc;

    Instructions::SNE_4xkk(&state);

    EXPECT_EQ(state.pc, pc);
}

TEST(LD_fx18, ShouldSetSoundTimerToRegisterValue) {
    CPUState state;
    unsigned short opcode = 0xf018;

    state.v[0] = 20;
    state.opcode = opcode;

    Instructions::LD_fx18(&state);

    EXPECT_EQ(state.soundTimer, 20);
}
