#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <Eigen/Dense>


class Light
{
public:
    Light();
    // 构造函数
    Light(const Eigen::Vector3f &position);

    // 设置光源位置
    void setPosition(const Eigen::Vector3f &position);
    Eigen::Vector3f getPosition() const;

    Eigen::Vector3f ambient() const;
    Eigen::Vector3f diffuse(Eigen::Vector3f vertexPosition, Eigen::Vector3f normal) const;
    Eigen::Vector3f specular(Eigen::Vector3f viewDirection, Eigen::Vector3f vertexPosition, Eigen::Vector3f normal) const;

private:
    Eigen::Vector3f position_; // 光源位置
    Eigen::Vector3f color_;    // 光源颜色

    float ambient_intensity_; // 环境光强度
    float diffuse_intensity_; // 漫反射强度
    float specular_intensity_; // 镜面反射强度
};

#endif// _LIGHT_H_