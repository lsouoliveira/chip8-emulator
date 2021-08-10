#include <gtest/gtest.h>
#include <cpu_state.h>
#include <instructions/set_delay_timer.h>
#include <video.h>

class SetDelayTimerTest : public ::testing::Test {
protected:
    Chip8::CPUState* cpu_state_;
    Chip8::SetDelayTimer* instruction_;

    SetDelayTimerTest()
    {
        instruction_ = new Chip8::SetDelayTimer();
    }

    ~SetDelayTimerTest()
    {
        delete instruction_;
    }

    void SetUp() override
    {
        cpu_state_ = new Chip8::CPUState();

        cpu_state_->v[0] = 20;
    }

    void TearDown() override
    {
        delete cpu_state_;
    }

};

TEST_F(SetDelayTimerTest, ShouldSetDelayTimerToRegisterValue) {
    unsigned short opcode = 0x7015;
    cpu_state_->opcode = opcode;

    instruction_->Process(cpu_state_);

    EXPECT_EQ(cpu_state_->delayTimer, 20); }
