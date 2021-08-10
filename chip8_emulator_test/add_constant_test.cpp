#include <gtest/gtest.h>
#include <cpu_state.h>
#include <instructions/add_constant.h>
#include <video.h>
#include <constants.h>

class AddConstantTest : public ::testing::Test {
protected:
    Chip8::CPUState* cpu_state_;
    Chip8::AddConstant* instruction_;

    AddConstantTest()
    {
        instruction_ = new Chip8::AddConstant();
    }

    ~AddConstantTest()
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

TEST_F(AddConstantTest, ShouldAddConstantToRegister) {
    unsigned short opcode = 0x7055;
    cpu_state_->opcode = opcode;

    instruction_->Process(cpu_state_);

    EXPECT_EQ(cpu_state_->v[0], 20 + 0x55); }
