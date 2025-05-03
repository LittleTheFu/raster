#ifndef _BASE_FS_H_
#define _BASE_FS_H_

#include "Vertex.h"
#include "gBufferData.h"
#include "light.h"
#include "colorBuffer.h"

class BaseFS
{
public:
    virtual void apply(const Vertex& vertex) = 0; // 纯虚函数，派生类必须实现
    
    virtual void setGBufferData(const std::shared_ptr<GBufferData>& gBufferData);
    virtual void setLight(const std::shared_ptr<Light>& light); // 设置光源
    virtual void setColorBuffer(std::shared_ptr<ColorBuffer>& colorBuffer); // 设置颜色缓冲区
};

#endif