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

    Eigen::Vector3f worldPos = gBufferData_->worldPositionBuffer.getBuffer(x, y); // 获取世界坐标数据

    if (worldPos.x() != 0)
    {
        int x = 3;
    }

    // shadow map test begin
    // bool isInside = true;
    // Eigen::Vector4f _worldPos{worldPos.x(), worldPos.y(), worldPos.z(), 1};
    // Eigen::Vector4f shadowPos = shadowMapMvpMatrix_ * _worldPos;
    // shadowPos /= shadowPos.w();
    // if (shadowPos.x() < -1 || shadowPos.x() > 1 || shadowPos.y() < -1 || shadowPos.y() > 1)
    // {
    //     isInside = false;
    // }

    // if (isInside)
    // {
    //     shadowPos = shadowMapNDCMatrix_ * shadowPos;
    //     if (!shadowZBuffer_->test(shadowPos.x(), shadowPos.y(), shadowPos.z() - 0.01f))
    //     {
    //         colorBuffer_->setPixel(x, y, 0, 0, 0, 255);
    //         return;
    //     }
    // }
    // shadow map test end

    Eigen::Vector2f texCoord = gBufferData_->uvBuffer.getBuffer(x, y);
    Eigen::Vector3f color = gBufferData_->colorBuffer.getBuffer(x, y);

    if (texture_)
    {
        uint8_t r, g, b;
        texture_->getColor(texCoord.x(), texCoord.y(), r, g, b); // 获取纹理颜色
        Eigen::Vector3f texColor(r, g, b);                       // 创建纹理颜色向量
        color = color.cwiseProduct(texColor);                    // 计算最终颜色
    }
    else
    {
        color *= 255.0f; // 如果没有纹理，则将颜色值乘以255
    }

    Eigen::Vector3f normal = gBufferData_->normalBuffer.getBuffer(x, y); // 获取法线数据
    float depth = gBufferData_->zBuffer.getDepth(x, y);                  // 获取深度数据

    Eigen::Vector3f ambient = light_->ambient();
    Eigen::Vector3f diffuse = light_->diffuse(worldPos, normal); // 计算漫反射光照

    // 计算镜面反射光照
    // Eigen::Vector3f viewDir = worldPos - eyePosition_; // 计算视线方向
    Eigen::Vector3f viewDir = -(worldPos - eyePosition_); // 计算视线方向
    viewDir.normalize();                                  // 归一化视线方向
    Eigen::Vector3f specular = light_->specular(viewDir, worldPos, normal);

    Eigen::Vector3f finalLight = ambient + diffuse + specular; // 计算最终光照

    // Eigen::Vector3f finalLight = specular; // 计算最终光照

    color = color.cwiseProduct(finalLight);                 // 计算最终颜色
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

void ScreenFS::setEyePosition(const Eigen::Vector3f &eyePosition)
{
    eyePosition_ = eyePosition; // 设置眼睛位置
}

void ScreenFS::setTexture(const std::shared_ptr<Texture> &texture)
{
    texture_ = texture; // 设置纹理数据
}

void ScreenFS::setShadowMapMvpMatrix(const Eigen::Matrix4f &shadowMapMvpMatrix)
{
    shadowMapMvpMatrix_ = shadowMapMvpMatrix;
}

void ScreenFS::setShadowMapNDCMatrix(const Eigen::Matrix4f &shadowMapNDCMatrix)
{
    shadowMapNDCMatrix_ = shadowMapNDCMatrix;
}

void ScreenFS::setShadowZBuffer(const std::shared_ptr<ZBuffer> &zBuffer)
{
    shadowZBuffer_ = zBuffer; // 设置阴影Z缓冲区数据
}