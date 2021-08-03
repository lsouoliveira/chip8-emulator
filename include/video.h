#ifndef VIDEO_H
#define VIDEO_H

#include <iostream>
#include <cstring>

#include <constants.h>

namespace Chip8 {

class Video {
private:
    unsigned char buffer_[VIDEO_BUFFER_SIZE];
public:
    Video();
    void ClearBuffer();
};

}

#endif /* VIDEO_H */
