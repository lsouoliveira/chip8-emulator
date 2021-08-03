#ifndef CHIP8_EMULATOR_H
#define CHIP8_EMULATOR_H

#include <iostream>
#include <vector>
#include <cpu.h>
#include <video.h>

namespace Chip8 {

class Chip8Emulator {
private:
    CPU* cpu_;
	Video* video_;
public:
    Chip8Emulator();
    ~Chip8Emulator();
    void Init();
    void Update();
	void Load(const std::vector<unsigned char>& buffer);
};

}

#endif /* CHIP8_EMULATOR_H */
