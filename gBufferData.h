#ifndef _G_BUFFER_DATA_H_
#define _G_BUFFER_DATA_H_

#include "zbuffer.h"
#include "vectorBuffer.h"
#include "uvBuffer.h"

class GBufferData
{
public:
    GBufferData(int width, int height);

    // 清空G缓冲区
    void clear();

public:
    VectorBuffer worldPositionBuffer; // 世界坐标缓冲区
    VectorBuffer normalBuffer; // 法线缓冲区
    VectorBuffer colorBuffer;
    ZBuffer zBuffer; // 深度缓冲区
    UVBuffer uvBuffer; // UV坐标缓冲区

    int width_;
    int height_;
};

#endif