#include <chip8_emulator.h>

namespace Chip8 {

Chip8Emulator::Chip8Emulator()
	: video_(new Video()),
	  cpu_(new CPU(video_))
{
}

Chip8Emulator::~Chip8Emulator()
{
	delete video_;
	delete cpu_;
}

void Chip8Emulator::Init()
{
	video_->ClearBuffer();
	cpu_->Init();
}

void Chip8Emulator::Update(double deltaTime)
{
	cpu_->Update(deltaTime);
}

void Chip8Emulator::Load(const std::vector<unsigned char>& buffer)
{
	cpu_->Load(buffer);
}

CPU* Chip8Emulator::cpu()
{
    return cpu_;
}

Video* Chip8Emulator::video()
{
    return video_;
}

}
