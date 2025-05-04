#ifndef _BASE_FS_H_
#define _BASE_FS_H_

#include "Vertex.h"
#include "gBufferData.h"
#include "light.h"
#include "colorBuffer.h"

#include <Eigen/Dense>

class BaseFS
{
public:
    virtual void apply(const Vertex& vertex) = 0; // 纯虚函数，派生类必须实现
    
    //kinds of params
    virtual void setGBufferData(const std::shared_ptr<GBufferData>& gBufferData);
    virtual void setLight(const std::shared_ptr<Light>& light); // 设置光源
    virtual void setColorBuffer(std::shared_ptr<ColorBuffer>& colorBuffer); // 设置颜色缓冲区
    virtual void setViewDir(const Eigen::Vector3f& viewDir); // 设置视线方向
    virtual void setEyePosition(const Eigen::Vector3f& eyePosition); // 设置眼睛位置
};

#endif