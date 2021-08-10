#include <gtest/gtest.h>
#include <cpu_state.h>
#include <instructions/read_sequence.h>
#include <video.h>
#include <constants.h>

class ReadSequenceTest : public ::testing::Test {
protected:
	Chip8::CPUState* cpu_state_;	
    Chip8::ReadSequence* instruction_;

    ReadSequenceTest()
	{
        instruction_ = new Chip8::ReadSequence();
	}

    ~ReadSequenceTest()
	{
        delete instruction_;
	}

    void SetUp() override
    {
		cpu_state_ = new Chip8::CPUState();

        for(int i = 0; i < 15; i++) {
            cpu_state_->v[i] = 0;
        }

        for(int i = 0; i <= 6; i++) {
            cpu_state_->memory[0x200 + i] = i + 1;
        }

        cpu_state_->i = 0x200;
    }

    void TearDown() override
    {
		delete cpu_state_;
    }

};

TEST_F(ReadSequenceTest, ShouldWriteAddressSequenceIntoRegisters) {
    unsigned short opcode = 0xf665;
	cpu_state_->opcode = opcode;

    instruction_->Process(cpu_state_);
	
    for(int i = 0; i <= 6; i++) {
        EXPECT_EQ(cpu_state_->v[i], i + 1);
    }
}
