#include "pipeline.h"

Pipeline::Pipeline(int width, int height)
{
    screenWidth_ = width;
    screenHeight_ = height;

    // 初始化模型矩阵、视图矩阵和投影矩阵
    modelMatrix_ = Eigen::Matrix4f::Identity();
    viewMatrix_ = Eigen::Matrix4f::Identity();
    projectionMatrix_ = Eigen::Matrix4f::Identity();
    mvpMatrix_ = Eigen::Matrix4f::Identity();
    ndcMatrix_ = Eigen::Matrix4f::Identity();

    isDirty_ = true; // 初始时需要更新MVP矩阵
}

void Pipeline::setModelMatrix(const Eigen::Matrix4f& modelMatrix)
{
    isDirty_ = true;
    modelMatrix_ = modelMatrix;
}

void Pipeline::setViewMatrix(const Eigen::Matrix4f& viewMatrix)
{
    isDirty_ = true;
    viewMatrix_ = viewMatrix;
}

void Pipeline::setProjectionMatrix(const Eigen::Matrix4f& projectionMatrix)
{
    isDirty_ = true;
    projectionMatrix_ = projectionMatrix;
}

const Eigen::Matrix4f& Pipeline::getMvpMatrix()
{
    if (isDirty_)
    {
        mvpMatrix_ = projectionMatrix_ * viewMatrix_ * modelMatrix_;
        isDirty_ = false;
    }
    return mvpMatrix_;
}

void Pipeline::calculateNDCMatrix()
{
    ndcMatrix_ = Eigen::Matrix4f::Identity();

    // 设置齐次坐标的缩放和平移
    ndcMatrix_(0, 0) = 0.5f * screenWidth_;  // x轴的缩放
    ndcMatrix_(1, 1) = 0.5f * screenHeight_; // y轴的缩放
    ndcMatrix_(0, 3) = 0.5f * screenWidth_;  // x轴的平移
    ndcMatrix_(1, 3) = 0.5f * screenHeight_; // y轴的平移

    // y轴翻转的处理
    ndcMatrix_(1, 1) *= -1.0f;
}
