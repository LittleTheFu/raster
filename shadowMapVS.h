#ifndef _SHADOW_MAP_VS_H_
#define _SHADOW_MAP_VS_H_

#include <Eigen/Dense>

#include "BaseVS.h"
#include "Vertex.h"

class ShadowMapVS : public BaseVS
{
public:
    ShadowMapVS();

    // 应用顶点着色器
    Vertex apply(const Vertex& vertex) const;
};

#endif