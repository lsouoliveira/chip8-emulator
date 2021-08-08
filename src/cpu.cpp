#include <cpu.h>

namespace Chip8 {

CPU::CPU(Video* video)
{
	instruction_map_ = new InstructionMap(std::vector<unsigned short>{0xFFFF, 0xF0FF, 0xF00F, 0xF000});
	instruction_map_->Add(0x00E0, new ClearScreenInstruction());
	instruction_map_->Add(0x6000, new MoveConstantInstruction());
	instruction_map_->Add(0xa000, new LoadIndexRegister());
	instruction_map_->Add(0xd000, new DrawSprite());

	state_.video = video;
}

CPU::~CPU()
{
	delete instruction_map_;
}

void CPU::Init()
{
    state_.pc = STARTING_MEMORY_ADDR;
    state_.opcode = 0;
    state_.i = 0;
    state_.sp = 0;

	state_.updateCounter = UPDATE_FREQUENCY;

    std::memset(state_.v, 0, NUM_REGISTERS);
    std::memset(state_.stack, 0, STACK_SIZE);
    std::memset(state_.memory, 0, MEMORY_SIZE);

    for(int i = 0; i < 80; i++) {
        state_.memory[i] = chip8_fontset[i];
    }
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
	Instruction* instruction = instruction_map_->Get(state_.opcode);
	if(instruction != nullptr) {
		spdlog::info("Instruction found \"{0:x}\"", state_.opcode);
		instruction->Process(&state_);
		std::cout << std::endl << state_.ToString() << std::endl;
	} else if(state_.opcode != 0) {
		spdlog::warn("Instruction not found \"{0:x}\"", state_.opcode);	
	}
	
	getchar();
}

void CPU::EmulateCycles(int numCycles)
{
	while(numCycles--) {
		FetchOpcode();
		EmulateInstruction();
	}
}

void CPU::Update(double deltaTime)
{
	state_.updateCounter -= deltaTime;	
	
	if(state_.updateCounter <= 0.0) {
		state_.updateCounter = UPDATE_FREQUENCY;
		
		EmulateCycles(CYCLES_PER_UPDATE);
		UpdateTimers();
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

}
