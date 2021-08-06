#include <gtest/gtest.h>
#include <cpu_state.h>
#include <instructions/load_index_register.h>
#include <video.h>
#include <constants.h>

class LoadIndexRegisterTest : public ::testing::Test {
protected:
	Chip8::CPUState* cpu_state_;	
	Chip8::LoadIndexRegister* instruction_;

	LoadIndexRegisterTest() 
	{
		instruction_ = new Chip8::LoadIndexRegister();
	}

	~LoadIndexRegisterTest() 
	{
		delete instruction_;
	}

    void SetUp() override
    {
		cpu_state_ = new Chip8::CPUState();
		cpu_state_->i = 0;
    }

    void TearDown() override
    {
		delete cpu_state_;
    }

};

TEST_F(LoadIndexRegisterTest, ShouldLoadRegisterIWithCorrectValue) {
	unsigned short opcode = 0xAFFF;
	cpu_state_->opcode = opcode;

	instruction_->Process(cpu_state_);
	
	EXPECT_EQ(cpu_state_->i, 0xFFF);
}
