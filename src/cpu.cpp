#include <cpu.h>

namespace Chip8 {

CPU::CPU(Video* video)
	: video_(video)
{
}

void CPU::Init()
{
    pc_ = STARTING_MEMORY_ADDR;
    opcode_ = 0;
    i_ = 0;
    sp_ = 0;

	update_counter_ = UPDATE_FREQUENCY;

    std::memset(v_, 0, sizeof(v_));
    std::memset(stack_, 0, sizeof(stack_));
    std::memset(memory_, 0, sizeof(memory_));

    for(int i = 0; i < 80; i++) {
        memory_[i] = chip8_fontset[i];
    }
}

void CPU::EmulateCycles(int numCycles)
{

}

void CPU::Update(double deltaTime)
{
	update_counter_ -= deltaTime;	
	
	if(update_counter_ <= 0.0) {
		update_counter_ = UPDATE_FREQUENCY;
			
		UpdateTimers();
	}
}

void CPU::UpdateTimers()
{
	delay_timer_ = std::max(0, delay_timer_ - 1);
	sound_timer_ = std::max(0, sound_timer_ - 1);
}

void CPU::Load(const std::vector<unsigned char>& buffer)
{
    for(size_t i = 0; i < buffer.size(); i++) {
        memory_[STARTING_MEMORY_ADDR + i] = buffer[i];
    }
}

}
