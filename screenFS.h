#ifndef _SCREEN_FS_H_
#define _SCREEN_FS_H_

#include "baseFS.h"
#include "light.h"
#include "colorBuffer.h"

class ScreenFS : public BaseFS
{
public:
    virtual void apply(const Vertex &vertex) override;

    virtual void setGBufferData(const std::shared_ptr<GBufferData> &gBufferData) override; // 设置GBuffer数据
    virtual void setLight(const std::shared_ptr<Light> &light) override; // 设置光源
    virtual void setColorBuffer(std::shared_ptr<ColorBuffer> &colorBuffer) override; // 设置颜色缓冲区
    virtual void setEyePosition(const Eigen::Vector3f& eyePosition) override; // 设置眼睛位置

private:
    std::shared_ptr<GBufferData> gBufferData_; // GBuffer数据
    std::shared_ptr<Light> light_; // 光源数据
    std::shared_ptr<ColorBuffer> colorBuffer_; // 颜色缓冲区数据

    Eigen::Vector3f eyePosition_; // 眼睛位置
};

#endif