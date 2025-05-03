#include "vertexShader.h"

VertexShader::VertexShader()
{
    modelMatrix_ = Eigen::Matrix4f::Identity();
    viewMatrix_ = Eigen::Matrix4f::Identity();
    projectionMatrix_ = Eigen::Matrix4f::Identity();
    mvpMatrix_ = Eigen::Matrix4f::Identity();

    isDirty_ = false;
}

Vertex VertexShader::apply(const Vertex& vertex)
{
    Vertex v = vertex;
    v.position = getMvpMatrix() * vertex.position; // 应用MVP矩阵变换

    return v;
}

// void VertexShader::setModelMatrix(const Eigen::Matrix4f& modelMatrix)
// {
//     modelMatrix_ = modelMatrix;
//     isDirty_ = true;
// }

// void VertexShader::setViewMatrix(const Eigen::Matrix4f& viewMatrix)
// {
//     viewMatrix_ = viewMatrix;
//     isDirty_ = true;
// }

// void VertexShader::setProjectionMatrix(const Eigen::Matrix4f& projectionMatrix)
// {
//     projectionMatrix_ = projectionMatrix;
//     isDirty_ = true;
// }

const Eigen::Matrix4f& VertexShader::getMvpMatrix()
{
    if (isDirty_)
    {
        mvpMatrix_ = projectionMatrix_ * viewMatrix_ * modelMatrix_;
        isDirty_ = false;
    }

    return mvpMatrix_;
}

void VertexShader::setMvpMatrix(const Eigen::Matrix4f& mvpMatrix)
{
    mvpMatrix_ = mvpMatrix;
    isDirty_ = false;
}