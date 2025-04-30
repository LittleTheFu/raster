#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <Eigen/Dense>
#include <array>

class Triangle {
public:
    Triangle();
    Triangle(const Eigen::Vector4f& v0, const Eigen::Vector4f& v1, const Eigen::Vector4f& v2);

    void setVertex(int index, const Eigen::Vector4f& vertex);
    const Eigen::Vector4f& vertex(int index) const;

    void div_w();

private:
    std::array<Eigen::Vector4f, 3> vertices_;
};

#endif // _TRIANGLE_H_