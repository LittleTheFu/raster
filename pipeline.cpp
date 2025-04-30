#include "pipeline.h"

Pipeline::Pipeline()
{
    // 初始化模型矩阵、视图矩阵和投影矩阵
    modelMatrix_ = Eigen::Matrix4f::Identity();
    viewMatrix_ = Eigen::Matrix4f::Identity();
    projectionMatrix_ = Eigen::Matrix4f::Identity();

    isMVPMatrixDirty_ = true; // 初始时需要更新MVP矩阵
}

void Pipeline::setModelMatrix(const Eigen::Matrix4f& modelMatrix)
{
    isMVPMatrixDirty_ = true;
    modelMatrix_ = modelMatrix;
}

void Pipeline::setViewMatrix(const Eigen::Matrix4f& viewMatrix)
{
    isMVPMatrixDirty_ = true;
    viewMatrix_ = viewMatrix;
}

void Pipeline::setProjectionMatrix(const Eigen::Matrix4f& projectionMatrix)
{
    isMVPMatrixDirty_ = true;
    projectionMatrix_ = projectionMatrix;
}

const Eigen::Matrix4f& Pipeline::getMvpMatrix()
{
    if (isMVPMatrixDirty_)
    {
        mvpMatrix_ = projectionMatrix_ * viewMatrix_ * modelMatrix_;
        isMVPMatrixDirty_ = false;
    }
    return mvpMatrix_;
}