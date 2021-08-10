#include <gtest/gtest.h>
#include <cpu_state.h>
#include <instructions/move_delay_timer.h>
#include <video.h>

class MoveDelayTimerTest : public ::testing::Test {
protected:
    Chip8::CPUState* cpu_state_;
    Chip8::MoveDelayTimer* instruction_;

    MoveDelayTimerTest()
    {
        instruction_ = new Chip8::MoveDelayTimer();
    }

    ~MoveDelayTimerTest()
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

TEST_F(MoveDelayTimerTest, ShouldMoveDelayTimerToRegister) {
    unsigned short opcode = 0x7007;
    cpu_state_->opcode = opcode;

    cpu_state_->delayTimer = 60;

    instruction_->Process(cpu_state_);

    EXPECT_EQ(cpu_state_->v[0], 60); }
