#ifndef _G_PASS_H_
#define _G_PASS_H_

#include "pass.h"

class GPass : public Pass
{
public:
    GPass(); // 构造函数，初始化GPass对象
    void run(const VertexBuffer& vertexBuffer); // 执行渲染通道
};

#endif