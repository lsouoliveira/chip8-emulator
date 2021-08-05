#include <gtest/gtest.h>
#include <cpu_state.h>
#include <instructions/clear_screen_instruction.h>
#include <video.h>
#include <constants.h>

class ClearScreenInstructionTest : public ::testing::Test {
protected:
	Chip8::CPUState* cpu_state_;	
	Chip8::Video* video_;
	Chip8::ClearScreenInstruction* instruction_;

	ClearScreenInstructionTest() 
	{
		instruction_ = new Chip8::ClearScreenInstruction();
	}

	~ClearScreenInstructionTest() 
	{
		delete instruction_;
	}

    void SetUp() override
    {
		cpu_state_ = new Chip8::CPUState();
		video_ = new Chip8::Video();

		cpu_state_->video = video_;
    }

    void TearDown() override
    {
		delete cpu_state_;
		delete video_;
    }

};

TEST_F(ClearScreenInstructionTest, ShouldClearScreenBuffer) {
    std::memset(cpu_state_->video, 1, sizeof(cpu_state_->video));
	instruction_->Process(cpu_state_);
	for (int i = 0; i < Chip8::VIDEO_BUFFER_SIZE; ++i) {
		EXPECT_EQ(cpu_state_->video->GetBuffer()[i], 0);
	}
}
