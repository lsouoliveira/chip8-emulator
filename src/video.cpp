#include <video.h>
namespace Chip8 {

Video::Video()
{

}

void Video::ClearBuffer()
{
    std::memset(buffer_, 0, sizeof(buffer_));
}

unsigned char* Video::GetBuffer()
{
	return buffer_;
}

}
