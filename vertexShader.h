#ifndef _VERTEX_SHADER_H_
#define _VERTEX_SHADER_H_

#include "Vertex.h"

#include <Eigen/Dense>

class VertexShader
{
public:
    VertexShader();

    Vertex apply(const Vertex& vertex) const;

    void setModelMatrix(const Eigen::Matrix4f& modelMatrix);
    void setViewMatrix(const Eigen::Matrix4f& viewMatrix);
    void setProjectionMatrix(const Eigen::Matrix4f& projectionMatrix);

private:
    void calculateMvpMatrix();

private:
    Eigen::Matrix4f modelMatrix_;
    Eigen::Matrix4f projectionMatrix_;
    Eigen::Matrix4f viewMatrix_;

    Eigen::Matrix4f mvpMatrix_;
};

#endif