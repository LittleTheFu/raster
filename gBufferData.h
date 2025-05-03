#ifndef _G_BUFFER_DATA_H_
#define _G_BUFFER_DATA_H_

#include "zbuffer.h"
#include "vectorBuffer.h"

class GBufferData
{
public:
    VectorBuffer worldPositionBuffer; // 世界坐标缓冲区
    VectorBuffer normalBuffer; // 法线缓冲区
    ZBuffer zBuffer; // 深度缓冲区
};

#endif