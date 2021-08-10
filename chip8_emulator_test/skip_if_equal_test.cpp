#include <gtest/gtest.h>
#include <cpu_state.h>
#include <instructions/skip_if_equal.h>
#include <video.h>

class SkipIfEqualTest : public ::testing::Test {
protected:
    Chip8::CPUState* cpu_state_;
    Chip8::SkipIfEqual* instruction_;

    SkipIfEqualTest()
    {
        instruction_ = new Chip8::SkipIfEqual();
    }

    ~SkipIfEqualTest()
    {
        delete instruction_;
    }

    void SetUp() override
    {
        cpu_state_ = new Chip8::CPUState();
    }

    void TearDown() override
    {
        delete cpu_state_;
    }

};

TEST_F(SkipIfEqualTest, ShouldSkipNextInstructionIfVxEqualToKk) {
    unsigned short opcode = 0x3042;
    cpu_state_->opcode = opcode;

    cpu_state_->pc = 0;
    cpu_state_->v[0] = 0x42;

    instruction_->Process(cpu_state_);

    EXPECT_EQ(cpu_state_->pc, 2);
}

TEST_F(SkipIfEqualTest, ShouldNotSkipNextInstructionIfVxDifferentToKk) {
    unsigned short opcode = 0x3044;
    cpu_state_->opcode = opcode;

    cpu_state_->pc = 0;
    cpu_state_->v[0] = 0x42;

    instruction_->Process(cpu_state_);

    EXPECT_EQ(cpu_state_->pc, 0);
}
