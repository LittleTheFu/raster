#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <Eigen/Dense>

class Vertex
{
public:
    Vertex &operator=(const Vertex &other);

    void clampColor(); // 限制颜色范围在0-1之间

    uint8_t r() const;
    uint8_t g() const;
    uint8_t b() const;

public:
    Eigen::Vector4f position;
    Eigen::Vector3f color;
    Eigen::Vector2f texCoord; // 纹理坐标
};

#endif // _VERTEX_H_