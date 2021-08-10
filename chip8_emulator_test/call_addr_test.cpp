#include <gtest/gtest.h>
#include <cpu_state.h>
#include <instructions/call_addr.h>
#include <video.h>
#include <constants.h>

class CallAddrTest : public ::testing::Test {
protected:
	Chip8::CPUState* cpu_state_;	
    Chip8::CallAddr* instruction_;

    CallAddrTest()
	{
        instruction_ = new Chip8::CallAddr();
	}

    ~CallAddrTest()
	{
        delete instruction_;
	}

    void SetUp() override
    {
		cpu_state_ = new Chip8::CPUState();

        cpu_state_->pc = 0x200;
        cpu_state_->sp = 0;

        for (int i = 0; i < Chip8::STACK_SIZE; ++i) {
            cpu_state_->stack[i] = 0;
		}
    }

    void TearDown() override
    {
		delete cpu_state_;
    }

};

TEST_F(CallAddrTest, ShouldSavePCInStackAndIncrementSP) {
    unsigned short opcode = 0x2222;
	cpu_state_->opcode = opcode;

    cpu_state_->pc += 2;

    instruction_->Process(cpu_state_);
	
    EXPECT_EQ(cpu_state_->sp, 1);
    EXPECT_EQ(cpu_state_->stack[0], 0x202);
    EXPECT_EQ(cpu_state_->pc, 0x222);
}
