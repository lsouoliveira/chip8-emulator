#include <gtest/gtest.h>
#include <cpu_state.h>
#include <instructions/instructions.h>
#include <video.h>
#include <constants.h>

using namespace Chip8;

TEST(AddConstantTest, ShouldAddConstantToRegister) {
    CPUState state;
    unsigned short opcode = 0x7055;

    state.v[0] = 20;
    state.opcode = opcode;

    Instructions::AddConstant(&state);

    EXPECT_EQ(state.v[0], 20 + 0x55);
}

TEST(AndRegistersTest, ShouldPerformBitwiseAndBetweenRegisters) {
    CPUState state;
    unsigned short opcode = 0x8012;
    unsigned char a = 228;
    unsigned char b = 176;

    state.opcode = opcode;

    state.v[0] = a;
    state.v[1] = b;

    Instructions::AndRegister(&state);

    EXPECT_EQ(state.v[0], a & b);
}

TEST(BcdTest, ShouldSavePCInStackAndIncrementSP) {
    CPUState state;
    unsigned short opcode = 0xf033;

    state.opcode = opcode;
    state.v[0] = 123;
    state.i = 0x200;

    Instructions::Bcd(&state);

    EXPECT_EQ(state.memory[state.i], 1);
    EXPECT_EQ(state.memory[state.i + 1], 2);
    EXPECT_EQ(state.memory[state.i + 2], 3);
}


TEST(CallAddrTest, ShouldSavePCInStackAndIncrementSP) {
    CPUState state;
    unsigned short opcode = 0x2222;
    state.opcode = opcode;

    state.pc = 0x200;
    state.sp = 0;

    for (int i = 0; i < Chip8::STACK_SIZE; ++i) {
        state.stack[i] = 0;
    }

    state.pc += 2;

    Instructions::CallAddr(&state);

    EXPECT_EQ(state.sp, 1);
    EXPECT_EQ(state.stack[0], 0x202);
    EXPECT_EQ(state.pc, 0x222);
}

TEST(ClearScreenInstructionTest, ShouldClearScreenBuffer) {
    CPUState state;
    Video video;
    state.video = &video;

    for (int i = 0; i < Chip8::VIDEO_BUFFER_SIZE; ++i) {
        state.video->GetBuffer()[i] = 1;
    }

    Instructions::ClearScreen(&state);

    for (int i = 0; i < Chip8::VIDEO_BUFFER_SIZE; ++i) {
        EXPECT_EQ(state.video->GetBuffer()[i], 0);
    }
}

TEST(LoadIndexRegisterTest, ShouldLoadRegisterIWithCorrectValue) {
    CPUState state;
    unsigned short opcode = 0xAFFF;

    state.opcode = opcode;
    state.i = 0;

    Instructions::LoadIndexRegister(&state);

    EXPECT_EQ(state.i, 0xFFF);
}

TEST(LoadRegisterWithConstant, ShouldLoadRegisterWithCorrectValue) {
    CPUState state;
    unsigned short opcode = 0x64FF;

    state.opcode = opcode;
    for (int i = 0; i < 15; ++i) {
        state.v[i] = 0;
    }

    Instructions::LoadRegisterWithConstant(&state);

    EXPECT_EQ(state.v[4], 0x00FF);
}

TEST(MoveDelayTimerTest, ShouldMoveDelayTimerToRegister) {
    CPUState state;
    unsigned short opcode = 0x7007;
    state.opcode = opcode;

    state.delayTimer = 60;

    Instructions::MoveDelayTimer(&state);

    EXPECT_EQ(state.v[0], 60);
}

TEST(ReadSequenceTest, ShouldWriteAddressSequenceIntoRegisters) {
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

    Instructions::ReadSequenceIntoRegisters(&state);

    for(int i = 0; i <= 6; i++) {
        EXPECT_EQ(state.v[i], i + 1);
    }
}

TEST(SetDelayTimerTest, ShouldSetDelayTimerToRegisterValue) {
    CPUState state;
    unsigned short opcode = 0x7015;

    state.v[0] = 20;
    state.opcode = opcode;

    Instructions::SetDelayTimer(&state);

    EXPECT_EQ(state.delayTimer, 20);
}

TEST(SkipIfEqualTest, ShouldSkipNextInstructionIfVxEqualToKk) {
    CPUState state;
    unsigned short opcode = 0x3042;
    state.opcode = opcode;

    state.pc = 0;
    state.v[0] = 0x42;

    Instructions::SkipIfEqual(&state);

    EXPECT_EQ(state.pc, 2);
}

TEST(SkipIfEqualTest, ShouldNotSkipNextInstructionIfVxDifferentToKk) {
    CPUState state;
    unsigned short opcode = 0x3044;
    state.opcode = opcode;

    state.pc = 0;
    state.v[0] = 0x42;

    Instructions::SkipIfEqual(&state);

    EXPECT_EQ(state.pc, 0);
}

TEST(SkipIfKeyNotPressedTest, ShouldSkipNextInstructionIfKeyNotPressed) {
    CPUState state;
    unsigned short opcode = 0xe0a1;
    unsigned short pc;

    state.opcode = opcode;
    state.pc = 0x200;
    state.v[0] = 0;
    state.key[0] = 0;
    pc = state.pc + 2;

    Instructions::SkipIfKeyNotPressed(&state);

    EXPECT_EQ(state.pc, pc);
}

TEST(SkipIfKeyNotPressedTest, ShouldNotSkipNextInstructionIfKeyIsPressed) {
    CPUState state;
    unsigned short opcode = 0xe0a1;
    unsigned short pc;

    state.pc = 0x200;
    state.opcode = opcode;
    state.v[0] = 0;
    state.key[0] = 1;
    pc = state.pc;

    Instructions::SkipIfKeyNotPressed(&state);

    EXPECT_EQ(state.pc, pc);
}

TEST(SpriteLocationTest, ShouldPointToFontSpriteLocation) {
    CPUState state;
    unsigned short opcode = 0xf029;

    state.opcode = opcode;
    state.v[0] = 0xC;

    Instructions::FontSpriteLocation(&state);

    EXPECT_EQ(state.i, 0xC * 5);
}



