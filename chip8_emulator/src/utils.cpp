#include <utils.h>

namespace Chip8
{

std::vector<unsigned char> ReadData(const std::string& filename)
{
	size_t filesize;
	std::ifstream file(filename, std::ios::binary);

    if(!file) {
        throw std::runtime_error("Invalid file");
    }

	file.seekg(0, std::ios::end);
	filesize = file.tellg();
	file.seekg(0, std::ios::beg);

	std::vector<char> buffer(filesize);
	file.read(&buffer[0], filesize);

	return std::vector<unsigned char>(buffer.begin(), buffer.end());
}

}
