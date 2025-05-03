#include "commonVS.h"

Vertex CommonVS::apply(const Vertex &vertex) const
{
    Vertex v = vertex;
    v.position = getMvpMatrix() * vertex.position; // 应用MVP矩阵变换

    return v;
}