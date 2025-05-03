#include "vectorBuffer.h"

VectorBuffer::VectorBuffer(int width, int height)
    : width(width), height(height),
      buffer(width * height, Eigen::Vector3f(0, 0, 0)) // 初始化缓冲区大小
{
}

const std::vector<Eigen::Vector3f> &VectorBuffer::getBuffer() const
{
    return buffer;
}

// 设置缓冲区中的向量数据
void VectorBuffer::setBuffer(int x, int y, const Eigen::Vector3f &value)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
    {
        buffer[y * width + x] = value;
    }
}

// 获取缓冲区中的向量数据
Eigen::Vector3f VectorBuffer::getBuffer(int x, int y) const
{
    if (x >= 0 && x < width && y >= 0 && y < height)
    {
        return buffer[y * width + x];
    }
    return Eigen::Vector3f(0, 0, 0); // 返回默认值
}

// 清空缓冲区
void VectorBuffer::clear()
{
    std::fill(buffer.begin(), buffer.end(), Eigen::Vector3f(0, 0, 0)); // 清空缓冲区
}

// 获取缓冲区的宽度和高度
int VectorBuffer::getWidth() const
{
    return width;
}

int VectorBuffer::getHeight() const
{
    return height;
}