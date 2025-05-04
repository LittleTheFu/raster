#ifndef _UV_BUFFER_H_
#define _UV_BUFFER_H_

//refactor later...maybe merge with vectorBuffer.h
//or maybe in the future we will use a texture to render to.
#include <Eigen/Dense>

class UVBuffer
{
public:
    UVBuffer(int width, int height);

    void clear(); // 清空缓冲区

    // 获取缓冲区的宽度和高度
    int getWidth() const;
    int getHeight() const;

    // 获取缓冲区中的向量数据
    const std::vector<Eigen::Vector2f>& getBuffer() const;

    // 设置缓冲区中的向量数据
    void setBuffer(int x, int y, const Eigen::Vector2f& value);

    // 获取缓冲区中的向量数据
    Eigen::Vector2f getBuffer(int x, int y) const;

private:
    std::vector<Eigen::Vector2f> buffer; // 存储向量数据
    
    int width; // 宽度
    int height; // 高度
};

#endif