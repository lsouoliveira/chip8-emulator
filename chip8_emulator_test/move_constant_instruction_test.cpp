#include <gtest/gtest.h>
#include <cpu_state.h>
#include <instructions/move_constant_instruction.h>
#include <video.h>
#include <constants.h>

class MoveConstantInstructionTest : public ::testing::Test {
protected:
	Chip8::CPUState* cpu_state_;	
    Chip8::MoveConstantInstruction* instruction_;

	MoveConstantInstructionTest() 
	{
        instruction_ = new Chip8::MoveConstantInstruction();
	}

	~MoveConstantInstructionTest() 
	{
        delete instruction_;
	}

    void SetUp() override
    {
		cpu_state_ = new Chip8::CPUState();

		for (int i = 0; i < 15; ++i) {
			cpu_state_->v[i] = 0;	
		}
    }

    void TearDown() override
    {
		delete cpu_state_;
    }

};

TEST_F(MoveConstantInstructionTest, ShouldLoadRegisterWithCorrectValue) {
	unsigned short opcode = 0x64FF;
	cpu_state_->opcode = opcode;

    instruction_->Process(cpu_state_);
	
	EXPECT_EQ(cpu_state_->v[4], 0x00FF);
}
