#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <Eigen/Dense>
#include <array>

class Triangle
{
public:
    using Vec4 = Eigen::Vector4f;

    Triangle();
    Triangle(const Vec4& v0, const Vec4& v1, const Vec4& v2);

    // 设置顶点
    void setVertex(int index, const Vec4& vertex);

    // 访问顶点
    const Vec4& vertex(int index) const;

private:
    std::array<Vec4, 3> vertices_;
};

#endif // _TRIANGLE_H_
