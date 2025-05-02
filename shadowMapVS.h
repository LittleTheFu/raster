#ifndef _SHADOW_MAP_VS_H_
#define _SHADOW_MAP_VS_H_

#include <Eigen/Dense>
#include "Vertex.h"

class ShadowMapVS
{
public:
    ShadowMapVS();

    // 应用顶点着色器
    Vertex apply(const Vertex& vertex) const;

    void setViewProjectionMatrix(const Eigen::Matrix4f& viewProjectionMatrix);

private:
    Eigen::Matrix4f viewProjectionMatrix_;
    Eigen::Matrix4f ndcMatrix_; // NDC矩阵

};

#endif