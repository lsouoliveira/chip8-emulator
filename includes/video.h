#ifndef VIDEO_H
#define VIDEO_H

#include <iostream>
#include <cstring>

#include <constants.h>

namespace Chip8 {

class Video {
private:
    unsigned char* buffer_;
public:
    Video();
	~Video();
    void ClearBuffer();
    unsigned char* GetBuffer();
};

}

#endif /* VIDEO_H */
