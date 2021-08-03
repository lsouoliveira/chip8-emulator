#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <vector>
#include <cstring>

#include <constants.h>
#include <video.h>

namespace Chip8 {

class CPU {
private:
    unsigned short opcode_;
    unsigned char memory_[MEMORY_SIZE];
    unsigned char v_[NUM_REGISTERS];
    unsigned short i_;
    unsigned short pc_;
    unsigned char delay_timer_;
    unsigned char sound_timer_;
    unsigned short stack_[STACK_SIZE];
    unsigned short sp_;
    unsigned char key_[NUM_KEYS];

    Video* video_;
public:
    CPU(Video* video);
    void Init();
    void NextCycle();
	void Load(const std::vector<unsigned char>& buffer);
};

}

#endif /* CPU_H */
