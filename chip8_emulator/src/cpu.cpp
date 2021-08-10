#include <cpu.h>

namespace Chip8 {

CPU::CPU(Video* video)
    : is_paused_(true)
{
	instruction_map_ = new InstructionMap(std::vector<unsigned short>{0xFFFF, 0xF0FF, 0xF00F, 0xF000});
    instruction_map_->Add(0x00E0, BIND_INSTRUCTION_CALLBACK(Instructions::ClearScreen));
    instruction_map_->Add(0x6000, BIND_INSTRUCTION_CALLBACK(Instructions::LoadRegisterWithConstant));
    instruction_map_->Add(0xa000, BIND_INSTRUCTION_CALLBACK(Instructions::LoadIndexRegister));
    instruction_map_->Add(0xd000, BIND_INSTRUCTION_CALLBACK(Instructions::DrawSprite));
    instruction_map_->Add(0x2000, BIND_INSTRUCTION_CALLBACK(Instructions::CallAddr));
    instruction_map_->Add(0xf033, BIND_INSTRUCTION_CALLBACK(Instructions::Bcd));
    instruction_map_->Add(0xf065, BIND_INSTRUCTION_CALLBACK(Instructions::ReadSequenceIntoRegisters));
    instruction_map_->Add(0xf029, BIND_INSTRUCTION_CALLBACK(Instructions::FontSpriteLocation));
    instruction_map_->Add(0x7000, BIND_INSTRUCTION_CALLBACK(Instructions::AddConstant));
    instruction_map_->Add(0x00ee, BIND_INSTRUCTION_CALLBACK(Instructions::Ret));
    instruction_map_->Add(0xf015, BIND_INSTRUCTION_CALLBACK(Instructions::SetDelayTimer));
    instruction_map_->Add(0xf007, BIND_INSTRUCTION_CALLBACK(Instructions::MoveDelayTimer));
    instruction_map_->Add(0x3000, BIND_INSTRUCTION_CALLBACK(Instructions::SkipIfEqual));
    instruction_map_->Add(0x1000, BIND_INSTRUCTION_CALLBACK(Instructions::Jump));
    instruction_map_->Add(0xc000, BIND_INSTRUCTION_CALLBACK(Instructions::RandomNumber));
    instruction_map_->Add(0xe0a1, BIND_INSTRUCTION_CALLBACK(Instructions::SkipIfKeyNotPressed));
    instruction_map_->Add(0x8002, BIND_INSTRUCTION_CALLBACK(Instructions::AndRegister));

	state_.video = video;
}

CPU::~CPU()
{
	delete instruction_map_;
}

void CPU::FetchOpcode()
{
	state_.opcode = state_.memory[state_.pc] << 8 | state_.memory[state_.pc + 1];
	state_.pc += 2;

	if(state_.pc >= MEMORY_SIZE) {
		state_.pc = MEMORY_SIZE - 1;
	}
}

void CPU::EmulateInstruction()
{
    auto instruction = instruction_map_->Get(state_.opcode);
    if(instruction) {
        std::cout << "Instruction found 0x" << std::hex << state_.opcode << std::endl;
        instruction(&state_);
	} else if(state_.opcode != 0) {
        std::cout << "Instruction not found 0x" << std::hex << state_.opcode << std::endl;
    }
}

void CPU::EmulateCycles(int numCycles)
{
	while(numCycles--) {
		FetchOpcode();
        EmulateInstruction();
	}
}

void CPU::Reset()
{
    state_.pc = STARTING_MEMORY_ADDR;
    state_.opcode = 0;
    state_.i = 0;
    state_.sp = 0;
    state_.delayTimer = 0;
    state_.soundTimer = 0;

    state_.updateCounter = UPDATE_FREQUENCY;

    for(int i = 0; i < MEMORY_SIZE; i++) {
        state_.memory[i] = 0;
    }

    for(int i = 0; i < STACK_SIZE; i++) {
        state_.stack[i] = 0;
    }

    for(int i = 0; i < NUM_REGISTERS; i++) {
        state_.v[i] = 0;
    }

    for(int i = 0; i < NUM_KEYS; i++) {
        state_.key[i] = 0;
    }

    for(int i = 0; i < 80; i++) {
        state_.memory[i] = chip8_fontset[i];
    }
}

void CPU::Update(double deltaTime)
{
	state_.updateCounter -= deltaTime;	

	if(state_.updateCounter <= 0.0) {
		state_.updateCounter = UPDATE_FREQUENCY;

        if(!is_paused_) {
            if(!is_debug_enabled_) {
                EmulateCycles(CYCLES_PER_UPDATE);
            }
            UpdateTimers();
        }
	}
}

void CPU::UpdateTimers()
{
	state_.delayTimer = std::max(0, state_.delayTimer - 1);
	state_.soundTimer = std::max(0, state_.soundTimer - 1);
}

void CPU::Load(const std::vector<unsigned char>& buffer)
{
    for(size_t i = 0; i < buffer.size(); i++) {
        state_.memory[STARTING_MEMORY_ADDR + i] = buffer[i];
    }
}

CPUState& CPU::state() {
    return state_;
}

void CPU::Start()
{
    is_paused_ = false;
}

void CPU::Pause()
{
    is_paused_ = true;
}

void CPU::SetDebug(bool enabled)
{
    is_debug_enabled_ = enabled;
}

bool CPU::is_paused()
{
    return is_paused_;
}

void CPU::Step()
{
    if(!is_paused() && is_debug_enabled_)
    FetchOpcode();
    EmulateInstruction();
}

bool CPU::is_debugging()
{
    return is_debug_enabled_;
}

void CPU::SetKeyState(unsigned char key, bool isPressed)
{
    if(key >= 0x0 && key <= 0xF) {
        state_.key[key] = (isPressed ? 1 : 0);
    }
}

}
