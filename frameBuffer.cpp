#include "frameBuffer.h"

// 构造函数，初始化帧缓冲区的大小
FrameBuffer::FrameBuffer(int width, int height)
    : colorBuffer(width, height), zBuffer(width, height)
{
}

// 获取颜色缓冲区
const ColorBuffer &FrameBuffer::getColorBuffer() const
{
    return colorBuffer;
}

// 获取深度缓冲区
const ZBuffer &FrameBuffer::getZBuffer() const
{
    return zBuffer;
}

// 设置一个像素的颜色和深度
bool FrameBuffer::testAndUpdate(int x, int y, float depth, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    if (zBuffer.testAndUpdate(x, y, depth))
    {                                           // 测试并更新深度缓冲区
        colorBuffer.setPixel(x, y, r, g, b, a); // 更新颜色缓冲区
        return true;                            // 更新成功
    }

    return false; // 更新失败
}

// 获取一个像素的颜色
void FrameBuffer::getPixel(int x, int y, uint8_t &r, uint8_t &g, uint8_t &b, uint8_t &a) const
{
    colorBuffer.getPixel(x, y, r, g, b, a);
}

// 清空帧缓冲区（颜色和深度）
void FrameBuffer::clear()
{
    colorBuffer.clearColor(0, 0, 0, 0); // 清空颜色缓冲区
    zBuffer.clear();                    // 清空深度缓冲区
}