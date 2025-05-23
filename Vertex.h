#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <Eigen/Dense>

class Vertex
{
public:
    Vertex &operator=(const Vertex &other);
    Vertex interpolate(const Vertex &other, float t) const;

    void clampColor(); // 限制颜色范围在0-1之间

    uint8_t r() const;
    uint8_t g() const;
    uint8_t b() const;

public:
    Eigen::Vector4f position;
    Eigen::Vector3f color;
    Eigen::Vector2f texCoord; // 纹理坐标
    Eigen::Vector3f normal; // 法线
    Eigen::Vector3f viewDir; // 视线方向
    Eigen::Vector3f worldPosition; // 世界坐标
};

#endif // _VERTEX_H_