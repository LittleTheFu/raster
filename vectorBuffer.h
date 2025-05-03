#ifndef _VECTOR_BUFFER_H_
#define _VECTOR_BUFFER_H_

#include <Eigen/Dense>

class VectorBuffer 
{
public:
    VectorBuffer(int width, int height);

    void clear(); // 清空缓冲区

    // 获取缓冲区的宽度和高度
    int getWidth() const;
    int getHeight() const;

    // 获取缓冲区中的向量数据
    const std::vector<Eigen::Vector3f>& getBuffer() const;

    // 设置缓冲区中的向量数据
    void setBuffer(int x, int y, const Eigen::Vector3f& value);

    // 获取缓冲区中的向量数据
    Eigen::Vector3f getBuffer(int x, int y) const;

private:
    std::vector<Eigen::Vector3f> buffer; // 存储向量数据
    
    int width; // 宽度
    int height; // 高度
};

#endif // _VECTOR_BUFFER_H_