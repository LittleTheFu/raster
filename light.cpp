#include "light.h"

Light::Light()
{
    position_ = Eigen::Vector3f(0, 0, 0); // 默认光源位置
    color_ = Eigen::Vector3f(1, 1, 1);     // 默认光源颜色

    ambient_intensity_ = 0.1f; // 环境光强度
    diffuse_intensity_ = 0.5f; // 漫反射强度
    specular_intensity_ = 1.0f; // 镜面反射强度
}

Light::Light(const Eigen::Vector3f &position)
    : position_(position)
{
    color_ = Eigen::Vector3f(1, 1, 1);

    ambient_intensity_ = 0.1f; // 环境光强度
    diffuse_intensity_ = 0.5f; // 漫反射强度
    specular_intensity_ = 1.0f; // 镜面反射强度
}

void Light::setPosition(const Eigen::Vector3f &position)
{
    position_ = position; // 设置光源位置
}

Eigen::Vector3f Light::ambient() const
{
    // 环境光分量 = 光源强度 * 颜色
    return ambient_intensity_ * color_; // 计算环境光分量
}

Eigen::Vector3f Light::diffuse(Eigen::Vector3f vertexPosition, Eigen::Vector3f normal) const
{
    Eigen::Vector3f lightDir = -(vertexPosition - position_).normalized(); // 光线方向
    float dotProduct = normal.dot(lightDir);                              // 计算点积
    if (dotProduct < 0.0f)
    {
        dotProduct = 0.0f; // 确保点积不为负值
    }
    // 计算漫反射分量
    return diffuse_intensity_ * color_ * dotProduct;
}

Eigen::Vector3f Light::specular(Eigen::Vector3f viewDirection, Eigen::Vector3f vertexPosition, Eigen::Vector3f normal) const
{
    Eigen::Vector3f lightDir = -(vertexPosition - position_).normalized();                     // 光线方向
    Eigen::Vector3f reflectDir = (2 * normal.dot(lightDir) * normal - lightDir).normalized(); // 反射方向
    float spec = std::pow(std::max(viewDirection.dot(reflectDir), 0.0f), 32);                 // 镜面反射分量
    return specular_intensity_ * color_ * spec;
}