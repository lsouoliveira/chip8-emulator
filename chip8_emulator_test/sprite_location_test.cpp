#include <gtest/gtest.h>
#include <cpu_state.h>
#include <instructions/sprite_location.h>
#include <video.h>
#include <constants.h>

class SpriteLocationTest : public ::testing::Test {
protected:
	Chip8::CPUState* cpu_state_;	
    Chip8::SpriteLocation* instruction_;

    SpriteLocationTest()
	{
        instruction_ = new Chip8::SpriteLocation();
	}

    ~SpriteLocationTest()
	{
        delete instruction_;
	}

    void SetUp() override
    {
		cpu_state_ = new Chip8::CPUState();

        cpu_state_->v[0] = 0xC;
    }

    void TearDown() override
    {
		delete cpu_state_;
    }

};

TEST_F(SpriteLocationTest, ShouldPointToFontSpriteLocation) {
    unsigned short opcode = 0xf029;
	cpu_state_->opcode = opcode;

    instruction_->Process(cpu_state_);
	
    EXPECT_EQ(cpu_state_->i, 0xC * 5);
}
