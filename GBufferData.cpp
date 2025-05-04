#include "gBufferData.h"

GBufferData::GBufferData(int width, int height)
    : worldPositionBuffer(width, height),
      normalBuffer(width, height),
      zBuffer(width, height),
      uvBuffer(width, height)
{
}

// 清空G缓冲区
void GBufferData::clear()
{
    worldPositionBuffer.clear();
    normalBuffer.clear();
    zBuffer.clear();
    uvBuffer.clear();
}