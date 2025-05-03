#ifndef _COMMON_VS_H_
#define _COMMON_VS_H_

#include "baseVS.h"

class CommonVS : public BaseVS
{
    public:
        Vertex apply(const Vertex& vertex) const override
        {
            // 这里可以添加自定义的顶点着色器逻辑
            return vertex; // 返回原始顶点
        }
};

#endif // _COMMON_VS_H_