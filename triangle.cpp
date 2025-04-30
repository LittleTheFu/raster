#include "triangle.h"
#include <stdexcept>

Triangle::Triangle()
{
    vertices_[0] = Eigen::Vector4f::Zero();
    vertices_[1] = Eigen::Vector4f::Zero();
    vertices_[2] = Eigen::Vector4f::Zero();
}

Triangle::Triangle(const Eigen::Vector4f& v0, const Eigen::Vector4f& v1, const Eigen::Vector4f& v2)
{
    vertices_[0] = v0;
    vertices_[1] = v1;
    vertices_[2] = v2;
}

void Triangle::setVertex(int index, const Eigen::Vector4f& vertex)
{
    if (index < 0 || index >= 3)
    {
        throw std::out_of_range("Triangle vertex index must be 0, 1, or 2.");
    }
    vertices_[index] = vertex;
}

const Eigen::Vector4f& Triangle::vertex(int index) const
{
    if (index < 0 || index >= 3)
    {
        throw std::out_of_range("Triangle vertex index must be 0, 1, or 2.");
    }
    return vertices_[index];
}