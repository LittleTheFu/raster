#ifndef _BASE_FS_H_
#define _BASE_FS_H_

#include "Vertex.h"

class BaseFS
{
public:
    virtual void apply(const Vertex& vertex) = 0; // 纯虚函数，派生类必须实现
};

#endif