#include "zbuffer.h"

ZBuffer::ZBuffer(int width, int height)
    : width_(width), height_(height)
{
    // 初始化 Z-buffer，所有像素的深度值设置为最大值
    buffer_.resize(width * height, std::numeric_limits<float>::max());
}

// 判断当前像素是否应该更新
bool ZBuffer::testAndUpdate(int x, int y, float depth)
{
    // 计算 Z-buffer 中对应的索引
    int index = y * width_ + x;

    if (index < 0 || index >= buffer_.size())
    {
        return false; // 超出范围，不更新
    }

    // 如果当前深度值小于 Z-buffer 中存储的值，则更新
    if (depth < buffer_[index])
    {
        buffer_[index] = depth;
        return true; // 更新成功
    }
    return false; // 不更新
}

// 测试当前像素的深度值是否小于 Z-buffer 中存储的值
bool ZBuffer::test(int x, int y, float depth) const
{
    // 计算 Z-buffer 中对应的索引
    int index = y * width_ + x;

    if (index < 0 || index >= buffer_.size())
    {
        return true;
    }

    // 如果当前深度值小于 Z-buffer 中存储的值，则返回 true
    return depth < buffer_[index];
}

int ZBuffer::height() const
{
    return height_;
}

int ZBuffer::width() const
{
    return width_;
}

// 获取 Z-buffer 中的深度值
float ZBuffer::getDepth(int x, int y) const
{
    int index = y * width_ + x;
    return buffer_[index];
}

// 清空 Z-buffer，将所有像素的深度值设置为最大值
void ZBuffer::clear()
{
    std::fill(buffer_.begin(), buffer_.end(), std::numeric_limits<float>::max());
}
