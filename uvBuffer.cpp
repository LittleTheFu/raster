#include "uvBuffer.h"

UVBuffer::UVBuffer(int width, int height)
    : width(width), height(height),
      buffer(width * height, Eigen::Vector2f(0, 0)) // 初始化缓冲区大小
{
}

const std::vector<Eigen::Vector2f> &UVBuffer::getBuffer() const
{
    return buffer;
}

// 设置缓冲区中的向量数据
void UVBuffer::setBuffer(int x, int y, const Eigen::Vector2f &value)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
    {
        buffer[y * width + x] = value;
    }
}

// 获取缓冲区中的向量数据
Eigen::Vector2f UVBuffer::getBuffer(int x, int y) const
{
    if (x >= 0 && x < width && y >= 0 && y < height)
    {
        return buffer[y * width + x];
    }
    return Eigen::Vector2f(0, 0); // 返回默认值
}

// 清空缓冲区
void UVBuffer::clear()
{
    std::fill(buffer.begin(), buffer.end(), Eigen::Vector2f(0.0f, 0.0f)); // 清空缓冲区
}

// 获取缓冲区的宽度和高度
int UVBuffer::getWidth() const
{
    return width;
}

int UVBuffer::getHeight() const
{
    return height;
}