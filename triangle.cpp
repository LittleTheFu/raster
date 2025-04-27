#include "triangle.h"
#include <stdexcept>

Triangle::Triangle()
{
    vertices_[0] = Vec4::Zero();
    vertices_[1] = Vec4::Zero();
    vertices_[2] = Vec4::Zero();
}

Triangle::Triangle(const Vec4& v0, const Vec4& v1, const Vec4& v2)
{
    vertices_[0] = v0;
    vertices_[1] = v1;
    vertices_[2] = v2;
}

void Triangle::setVertex(int index, const Vec4& vertex)
{
    if (index < 0 || index >= 3)
    {
        throw std::out_of_range("Triangle vertex index must be 0, 1, or 2.");
    }
    vertices_[index] = vertex;
}

const Triangle::Vec4& Triangle::vertex(int index) const
{
    if (index < 0 || index >= 3)
    {
        throw std::out_of_range("Triangle vertex index must be 0, 1, or 2.");
    }
    return vertices_[index];
}
