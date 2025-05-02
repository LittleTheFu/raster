#include "colorBuffer.h"

// 构造函数，初始化颜色缓冲区大小
ColorBuffer::ColorBuffer(int width, int height)
    : width_(width), height_(height), buffer_((width * height) * 4, 0) // 初始化缓冲区大小
{
}

// 获取图像的宽度和高度
int ColorBuffer::width() const {
    return width_;
}

int ColorBuffer::height() const {
    return height_;
}

// 设置一个像素的颜色 (r, g, b, a)
void ColorBuffer::setPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    assert(x >= 0 && x < width_ && y >= 0 && y < height_);

    // 计算该像素在缓冲区中的索引
    int index = (y * width_ + x) * 4; // 每个像素有 4 个字节（RGBA）
    buffer_[index + 0] = a; // 红色
    buffer_[index + 1] = b; // 绿色
    buffer_[index + 2] = g; // 蓝色
    buffer_[index + 3] = r; // 透明度
}

// 获取某个像素的颜色 (r, g, b, a)
void ColorBuffer::getPixel(int x, int y, uint8_t& r, uint8_t& g, uint8_t& b, uint8_t& a) const {
    assert(x >= 0 && x < width_ && y >= 0 && y < height_);

    // 计算该像素在缓冲区中的索引
    int index = (y * width_ + x) * 4;
    r = buffer_[index + 0]; // 红色
    g = buffer_[index + 1]; // 绿色
    b = buffer_[index + 2]; // 蓝色
    a = buffer_[index + 3]; // 透明度
}

// 清空颜色缓冲区，填充为指定颜色
void ColorBuffer::clearColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            setPixel(x, y, r, g, b, a);
        }
    }
}

// 获取颜色缓冲区的数据指针
const std::vector<uint8_t>& ColorBuffer::getBuffer() const {
    return buffer_;
}