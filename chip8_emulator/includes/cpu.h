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
#include <config.h>
#include <instructions/instruction_map.h>
#include <instructions/instructions.h>

namespace Chip8 {

class CPU {
private:
	CPUState state_;
    Config* config_;
    bool is_paused_;
    bool is_debug_enabled_;
	
	void FetchOpcode();
	void EmulateInstruction();
public:
    CPU(Video* video, Config* config);
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
