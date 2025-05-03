#ifndef _G_PASS_H_
#define _G_PASS_H_

#include "pass.h"
#include "gBufferData.h"


class GPass : public Pass
{
public:
    GPass(int witdh, int height); // 构造函数，初始化GPass对象

    void preRun() override; // 渲染前的准备工作
    const std::shared_ptr<GBufferData>& getGBufferData() const;

private:
    std::shared_ptr<GBufferData> gBufferData_; // G缓冲区数据对象
};

#endif