#ifndef _COLORBUFFER_H_
#define _COLORBUFFER_H_

#include <vector>
#include <iostream>
#include <cassert>

class ColorBuffer {
public:
    // 构造函数，初始化颜色缓冲区大小
    ColorBuffer(int width, int height);

    // 获取图像的宽度和高度
    int width() const;
    int height() const;

    // 设置一个像素的颜色 (r, g, b, a)
    void setPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    // 获取某个像素的颜色 (r, g, b, a)
    void getPixel(int x, int y, uint8_t& r, uint8_t& g, uint8_t& b, uint8_t& a) const;

    // 清空颜色缓冲区，填充为指定颜色
    void clearColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    // 获取颜色缓冲区的数据指针
    const std::vector<uint8_t>& getBuffer() const;

private:
    int width_, height_;                  // 图像的宽度和高度
    std::vector<uint8_t> buffer_;         // 存储颜色数据（RGBA）
};

#endif // COLORBUFFER_H