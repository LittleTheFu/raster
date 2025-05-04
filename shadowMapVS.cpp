#include "shadowMapVS.h"

ShadowMapVS::ShadowMapVS()
{
}

Vertex ShadowMapVS::apply(const Vertex& vertex) const
{
    Vertex v = vertex;
    v.position = getMvpMatrix() * vertex.position; // 应用MVP矩阵变换

    return v;
}