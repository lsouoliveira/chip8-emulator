#include <gtest/gtest.h>
#include <cpu_state.h>
#include <instructions/bcd.h>
#include <video.h>
#include <constants.h>

class BcdTest : public ::testing::Test {
protected:
	Chip8::CPUState* cpu_state_;	
    Chip8::Bcd* instruction_;

    BcdTest()
	{
        instruction_ = new Chip8::Bcd();
	}

    ~BcdTest()
	{
        delete instruction_;
	}

    void SetUp() override
    {
		cpu_state_ = new Chip8::CPUState();

        cpu_state_->v[0] = 123;
        cpu_state_->i = 0x200;
    }

    void TearDown() override
    {
		delete cpu_state_;
    }

};

TEST_F(BcdTest, ShouldSavePCInStackAndIncrementSP) {
    unsigned short opcode = 0xf033;
	cpu_state_->opcode = opcode;

    instruction_->Process(cpu_state_);
	
    EXPECT_EQ(cpu_state_->memory[cpu_state_->i], 1);
    EXPECT_EQ(cpu_state_->memory[cpu_state_->i + 1], 2);
    EXPECT_EQ(cpu_state_->memory[cpu_state_->i + 2], 3);
}
