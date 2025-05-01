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

    calculateNDCMatrix(); // 计算NDC矩阵

    isDirty_ = true; // 初始时需要更新MVP矩阵
}

void Pipeline::setModelMatrix(const Eigen::Matrix4f& modelMatrix)
{
    vertexShader_.setModelMatrix(modelMatrix); // 设置模型矩阵
}

void Pipeline::setViewMatrix(const Eigen::Matrix4f& viewMatrix)
{
    vertexShader_.setViewMatrix(viewMatrix); // 设置视图矩阵
}

void Pipeline::setProjectionMatrix(const Eigen::Matrix4f& projectionMatrix)
{
    vertexShader_.setProjectionMatrix(projectionMatrix);
}

Vertex Pipeline::getScreenVertex(const Vertex &vertex)
{
    Vertex vertexNdc = vertexShader_.apply(vertex); // 应用顶点着色器
    vertexNdc.position /= vertexNdc.position.w();
    vertexNdc.position = ndcMatrix_ * vertexNdc.position; // 转换到NDC坐标系

    return vertexNdc; // 返回x, y, z坐标
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
