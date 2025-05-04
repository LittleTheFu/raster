#include "screenPass.h"

ScreenPass::ScreenPass(int width, int height)
    : Pass(width, height)
{
    // 初始化颜色缓冲区
    colorBuffer = std::make_shared<ColorBuffer>(width, height);

    vertexShader_ = std::make_unique<ScreenVS>();
    fragmentShader_ = std::make_unique<ScreenFS>();

    fragmentShader_->setColorBuffer(colorBuffer); // 设置颜色缓冲区
}

const std::shared_ptr<ColorBuffer> &ScreenPass::getColorBuffer() const
{
    return colorBuffer;
}

void ScreenPass::preRun()
{
    // vertexShader_->setMvpMatrix(projectionMatrix_);
}

void ScreenPass::setLight(const std::shared_ptr<Light> &light)
{
    if (fragmentShader_)
        fragmentShader_->setLight(light);
}

void ScreenPass::setGBufferData(const std::shared_ptr<GBufferData> &gBufferData)
{
    if (fragmentShader_)
        fragmentShader_->setGBufferData(gBufferData);
}

void ScreenPass::setEyePosition(const Eigen::Vector3f &eyePosition)
{
    if (fragmentShader_)
        fragmentShader_->setEyePosition(eyePosition);
}