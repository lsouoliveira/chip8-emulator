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
    Reset();
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

void Chip8Emulator::SetKeyState(unsigned char key, bool isPressed)
{
    cpu_->SetKeyState(key, isPressed);
}

void Chip8Emulator::Reset()
{
    cpu_->Reset();
    video_->ClearBuffer();
}

void Chip8Emulator::Start()
{
    cpu_->Start();
}

}
