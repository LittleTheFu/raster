#ifndef _PASS_H_
#define _PASS_H_

#include <Eigen/Dense>
#include "vertexBuffer.h"
#include "vertexShader.h"
#include "fragmentShader.h"

class Pass
{     
public: 
    void setProjectionMatrix(const Eigen::Matrix4f &projectionMatrix);

    void run(const VertexBuffer& vertexBuffer); // 执行渲染通道

private:
    Vertex getScreenVertex(const Vertex& vertex); // 获取屏幕坐标的顶点
    void Pass::drawScreenTriangle(const Vertex &v0, const Vertex &v1, const Vertex &v2);

private:
    Eigen::Matrix4f projectionMatrix_;
    Eigen::Matrix4f ndcMatrix_; // NDC矩阵

    VertexShader vertexShader_; // 顶点着色器对象
    FragmentShader fragmentShader_; // 片段着色器对象
};

#endif