#ifndef CHIP8_EMULATOR_H
#define CHIP8_EMULATOR_H

#include <iostream>
#include <vector>
#include <cpu.h>
#include <video.h>
#include <instructions/instruction.h>
#include <instructions/clear_screen_instruction.h>
#include <instructions/instruction_map.h>

namespace Chip8 {

class Chip8Emulator {
private:
	Video* video_;
    CPU* cpu_;
public:
    Chip8Emulator();
    ~Chip8Emulator();
    void Init();
    void Update(double deltaTime);
	void Load(const std::vector<unsigned char>& buffer);
};

}

#endif /* CHIP8_EMULATOR_H */
