#include "shadowMapVS.h"

ShadowMapVS::ShadowMapVS()
{
    viewProjectionMatrix_ = Eigen::Matrix4f::Identity();
}

Vertex ShadowMapVS::apply(const Vertex& vertex) const
{
    Vertex v = vertex;
    v.position = viewProjectionMatrix_ * vertex.position; // 应用MVP矩阵变换

    return v;
}

void ShadowMapVS::setViewProjectionMatrix(const Eigen::Matrix4f &viewProjectionMatrix)
{
    viewProjectionMatrix_ = viewProjectionMatrix;
}