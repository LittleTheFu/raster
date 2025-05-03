#ifndef _BASE_FS_H_
#define _BASE_FS_H_

#include "Vertex.h"
#include "gBufferData.h"

class BaseFS
{
public:
    virtual void apply(const Vertex& vertex) = 0; // 纯虚函数，派生类必须实现
    virtual void setGBufferData(const std::shared_ptr<GBufferData>& gBufferData) = 0;

};

#endif