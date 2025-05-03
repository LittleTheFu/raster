#ifndef _PASS_H_
#define _PASS_H_

#include <Eigen/Dense>
#include "baseFS.h"
#include "baseVS.h"
#include "vertexBuffer.h"
#include "light.h"
#include "gBufferData.h"

class Pass
{     
public:
    Pass(int width, int height); // 构造函数，初始化Pass对象
    void setProjectionMatrix(const Eigen::Matrix4f &projectionMatrix);

    virtual void preRun(); // 渲染前的准备工作
    void run(const VertexBuffer& vertexBuffer); // 执行渲染通道

    virtual void setLight(const std::shared_ptr<Light>& light); // 设置光源
    virtual void setGBufferData(const std::shared_ptr<GBufferData>& gBufferData); // 设置GBuffer数据

private:
    void calculateNDCMatrix();
    Vertex getScreenVertex(const Vertex& vertex); // 获取屏幕坐标的顶点
    void Pass::drawScreenTriangle(const Vertex &v0, const Vertex &v1, const Vertex &v2);

protected:
    Eigen::Matrix4f projectionMatrix_;
    Eigen::Matrix4f ndcMatrix_; // NDC矩阵

    std::unique_ptr<BaseVS> vertexShader_; // 顶点着色器对象
    std::unique_ptr<BaseFS> fragmentShader_; // 片段着色器对象

    int width_;
    int height_;
};

#endif