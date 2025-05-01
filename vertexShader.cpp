#include "vertexShader.h"

VertexShader::VertexShader()
{
    modelMatrix_ = Eigen::Matrix4f::Identity();
    viewMatrix_ = Eigen::Matrix4f::Identity();
    projectionMatrix_ = Eigen::Matrix4f::Identity();
    mvpMatrix_ = Eigen::Matrix4f::Identity();
}

Vertex VertexShader::apply(const Vertex& vertex) const
{
    Vertex v = vertex;
    v.position = mvpMatrix_ * vertex.position; // 应用MVP矩阵变换

    return v;
}

void VertexShader::setModelMatrix(const Eigen::Matrix4f& modelMatrix)
{
    modelMatrix_ = modelMatrix;
    calculateMvpMatrix();
}

void VertexShader::setViewMatrix(const Eigen::Matrix4f& viewMatrix)
{
    viewMatrix_ = viewMatrix;
    calculateMvpMatrix();
}

void VertexShader::setProjectionMatrix(const Eigen::Matrix4f& projectionMatrix)
{
    projectionMatrix_ = projectionMatrix;
    calculateMvpMatrix();
}

void VertexShader::calculateMvpMatrix()
{
    mvpMatrix_ = projectionMatrix_ * viewMatrix_ * modelMatrix_;
}