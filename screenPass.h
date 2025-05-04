#ifndef _SCREEN_PASS_H_
#define _SCREEN_PASS_H_ 

#include "pass.h"
#include "screenVS.h" // 屏幕顶点着色器头文件
#include "screenFS.h" // 屏幕片段着色器头文件
#include "vertexBuffer.h" // 顶点缓冲区头文件
#include "colorBuffer.h" // 颜色缓冲区头文件

class ScreenPass : public Pass 
{ 
public:
    ScreenPass(int width, int height); // 构造函数，初始化ScreenPass对象

    virtual void preRun() override; // 渲染前的准备工作

    virtual void setLight(const std::shared_ptr<Light>& light) override; // 设置光源
    virtual void setGBufferData(const std::shared_ptr<GBufferData>& gBufferData) override; // 设置GBuffer数据
    virtual void setEyePosition(const Eigen::Vector3f& eyePosition) override; // 设置眼睛位置
    virtual void setTexture(const std::shared_ptr<Texture>& texture) override; // 设置纹理

    const std::shared_ptr<ColorBuffer>& getColorBuffer() const; // 获取颜色缓冲区

private:
    VertexBuffer screenVertexBuffer;
    std::shared_ptr<ColorBuffer> colorBuffer; // 颜色缓冲区对象
};

#endif// _SCREEN_PASS_H_