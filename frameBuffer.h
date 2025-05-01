#ifndef _FRAME_BUFFER_H_
#define _FRAME_BUFFER_H_

#include "zbuffer.h"
#include "colorBuffer.h"

class FrameBuffer {
public:
    // 构造函数，初始化帧缓冲区的大小
    FrameBuffer(int width, int height);

    // 获取颜色缓冲区
    ColorBuffer& getColorBuffer();

    // 获取深度缓冲区
    ZBuffer& getZBuffer();

    // 设置一个像素的颜色和深度
    void setPixel(int x, int y, float depth, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    // 获取一个像素的颜色
    void getPixel(int x, int y, float& r, uint8_t& g, uint8_t& b, uint8_t& a) const;

    // 清空帧缓冲区（颜色和深度）
    void clear();

private:
    ColorBuffer colorBuffer; // 颜色缓冲区
    ZBuffer zBuffer;         // 深度缓冲区
};

#endif // _FRAME_BUFFER_H_