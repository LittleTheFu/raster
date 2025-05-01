#ifndef _FRAME_BUFFER_H_
#define _FRAME_BUFFER_H_ 

#include "zbuffer.h"
#include "colorBuffer.h"

class FrameBuffer {

private:
    ColorBuffer colorBuffer; // 颜色缓冲区
    ZBuffer zBuffer;         // 深度缓冲区
};

#endif// frameBuffer.h