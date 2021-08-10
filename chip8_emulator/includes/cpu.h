#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <functional>
#include <unordered_map>

// #include <spdlog/spdlog.h>

#include <constants.h>
#include <video.h>
#include <cpu_state.h>
#include <instructions/instruction_map.h>
#include <instructions/clear_screen_instruction.h>
#include <instructions/move_constant_instruction.h>
#include <instructions/load_index_register.h>
#include <instructions/draw_sprite.h>
#include <instructions/call_addr.h>
#include <instructions/bcd.h>
#include <instructions/read_sequence.h>
#include <instructions/sprite_location.h>
#include <instructions/add_constant.h>
#include <instructions/ret.h>
#include <instructions/set_delay_timer.h>
#include <instructions/move_delay_timer.h>
#include <instructions/skip_if_equal.h>
#include <instructions/jump.h>
#include <instructions/random_number.h>

class Instruction;

namespace Chip8 {

class CPU {
private:
	CPUState state_;
	InstructionMap* instruction_map_;
    bool is_paused_;
    bool is_debug_enabled_;
	
	void FetchOpcode();
	void EmulateInstruction();
public:
    CPU(Video* video);
	~CPU();
    void EmulateCycles(int numCycles);
	void Update(double deltaTime);
	void UpdateTimers();
	void Load(const std::vector<unsigned char>& buffer);
    void Start();
    void Pause();
    CPUState& state();
    bool is_paused();
    void Step();
    void Reset();
    void SetDebug(bool enabled);
    bool is_debugging();
    void SetKeyState(unsigned char key, bool isPressed);
};

}

#endif /* CPU_H */
