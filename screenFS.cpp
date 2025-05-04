#include "screenFS.h"
#include <Eigen/Dense>

void ScreenFS::apply(const Vertex &vertex)
{
    int x = static_cast<int>(vertex.position.x()); // 获取顶点位置的x坐标
    int y = static_cast<int>(vertex.position.y()); // 获取顶点位置的y坐标
    if (x < 0 || x >= colorBuffer_->width() || y < 0 || y >= colorBuffer_->height())
    {
        return; // 超出范围，返回
    }

    float u = vertex.texCoord.x();
    float v = vertex.texCoord.y();

    Eigen::Vector3f color = vertex.color; // 获取顶点颜色
    Eigen::Vector3f worldPos = gBufferData_->worldPositionBuffer.getBuffer(x, y); // 获取世界坐标数据
    
    Eigen::Vector3f normal = gBufferData_->normalBuffer.getBuffer(x, y); // 获取法线数据
    float depth = gBufferData_->zBuffer.getDepth(x, y); // 获取深度数据

    Eigen::Vector3f ambient = light_->ambient();
    Eigen::Vector3f diffuse = light_->diffuse(worldPos, normal); // 计算漫反射光照

    // 计算镜面反射光照
    Eigen::Vector3f viewDir = worldPos - eyePosition_; // 计算视线方向
    viewDir.normalize(); // 归一化视线方向
    Eigen::Vector3f specular = light_->specular(viewDir, vertex.worldPosition, vertex.normal);

    Eigen::Vector3f finalLight = ambient + diffuse + specular; // 计算最终光照

    color = color.cwiseProduct(finalLight); // 计算最终颜色
    color *= 255; // 将颜色值转换为0-255范围
    color = color.cwiseMin(Eigen::Vector3f(255, 255, 255)); // 限制颜色范围在0-255之间

    colorBuffer_->setPixel(x, y, static_cast<uint8_t>(color(0)), static_cast<uint8_t>(color(1)), static_cast<uint8_t>(color(2)), 255);
}

void ScreenFS::setGBufferData(const std::shared_ptr<GBufferData> &gBufferData)
{
    gBufferData_ = gBufferData; // 设置GBuffer数据
}

void ScreenFS::setLight(const std::shared_ptr<Light> &light)
{
    light_ = light; // 设置光源数据
}

void ScreenFS::setColorBuffer(std::shared_ptr<ColorBuffer> &colorBuffer)
{
    colorBuffer_ = colorBuffer; // 设置颜色缓冲区数据
}

void ScreenFS::setEyePosition(const Eigen::Vector3f& eyePosition)
{
    eyePosition_ = eyePosition; // 设置眼睛位置
}