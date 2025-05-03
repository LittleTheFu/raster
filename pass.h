#ifndef _PASS_H_
#define _PASS_H_

#include <Eigen/Dense>
#include "baseFS.h"
#include "baseVS.h"
#include "vertexBuffer.h"

class Pass
{     
public: 
    void setProjectionMatrix(const Eigen::Matrix4f &projectionMatrix);

    void run(const VertexBuffer& vertexBuffer); // 执行渲染通道

private:
    Vertex getScreenVertex(const Vertex& vertex); // 获取屏幕坐标的顶点
    void Pass::drawScreenTriangle(const Vertex &v0, const Vertex &v1, const Vertex &v2);

protected:
    Eigen::Matrix4f projectionMatrix_;
    Eigen::Matrix4f ndcMatrix_; // NDC矩阵

    std::unique_ptr<BaseVS> vertexShader_; // 顶点着色器对象
    std::unique_ptr<BaseFS> fragmentShader_; // 片段着色器对象
};

#endif