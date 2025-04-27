#ifndef CAMERA_H
#define CAMERA_H

#include <Eigen/Dense>
#include <cmath>
#include <iostream>

class Camera {
public:
    // 相机位置、朝向、上方向
    Eigen::Vector3f position;
    Eigen::Vector3f viewDirection;
    Eigen::Vector3f upDirection;

    // 投影相关
    float fov;      // 视野 (Field of View)，单位：度
    float nearClip; // 近裁剪面
    float farClip;  // 远裁剪面
    float aspect;   // 宽高比

    // 构造函数
    Camera(const Eigen::Vector3f& pos, const Eigen::Vector3f& target, const Eigen::Vector3f& up,
           float fov = 45.0f, float aspect = 16.0f/9.0f, float nearClip = 0.1f, float farClip = 100.0f);

    // 生成视图矩阵
    Eigen::Matrix4f getViewMatrix() const;

    // 生成投影矩阵（透视投影）
    Eigen::Matrix4f getProjectionMatrix() const;

    // 设置相机位置
    void setPosition(const Eigen::Vector3f& newPos);

    // 设置目标位置
    void setTarget(const Eigen::Vector3f& target);

    // 设置视野角度
    void setFOV(float newFov);

    // 设置近裁剪面和远裁剪面
    void setClippingPlanes(float near, float far);

    // 设置宽高比
    void setAspect(float newAspect);

    // 打印相机信息
    void printCameraInfo() const;
};

#endif // CAMERA_H
