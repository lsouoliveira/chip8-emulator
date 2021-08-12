#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>

namespace Chip8 {

std::vector<unsigned char> ReadData(const std::string& filename);

}

#endif
