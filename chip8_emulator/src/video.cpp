#include <video.h>
#include <iostream>

namespace Chip8 {

Video::Video()
{
	buffer_ = new unsigned char[VIDEO_BUFFER_SIZE];
}

Video::~Video()
{
}

void Video::ClearBuffer()
{
	for (int i = 0; i < VIDEO_BUFFER_SIZE; ++i) {
		buffer_[i] = 0;
	}
}

unsigned char* Video::GetBuffer()
{
	return buffer_;
}

}
