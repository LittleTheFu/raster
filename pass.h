#ifndef _PASS_H_
#define _PASS_H_

#include <Eigen/Dense>
#include "baseFS.h"
#include "baseVS.h"
#include "vertexBuffer.h"
#include "light.h"
#include "gBufferData.h"
#include "zbuffer.h"
#include <array>
#include "shadowMapCamera.h"


class Pass
{     
public:
    Pass(int width, int height); // 构造函数，初始化Pass对象

    void setMvpMatrix(const Eigen::Matrix4f &projectionMatrix);
    const Eigen::Matrix4f& getNDCMatrix() const;
    const Eigen::Matrix4f& getMvpMatrix() const;

    virtual void preRun(); // 渲染前的准备工作
    void run(const VertexBuffer& vertexBuffer); // 执行渲染通道

    virtual void setLight(const std::shared_ptr<Light>& light); // 设置光源
    virtual void setGBufferData(const std::shared_ptr<GBufferData>& gBufferData); // 设置GBuffer数据
    virtual void setEyePosition(const Eigen::Vector3f& eyePosition); // 设置眼睛位置
    virtual void setTexture(const std::shared_ptr<Texture>& texture); // 设置纹理

    virtual void setShadowZBuffer(const std::shared_ptr<ZBuffer>& zBuffer);
    virtual void setShadowMapMvpMatrix(const Eigen::Matrix4f& shadowMapMvpMatrix);
    virtual void setShadowMapNDCMatrix(const Eigen::Matrix4f& shadowMapNDCMatrix);

    virtual void setShadowMapCamera(const std::shared_ptr<ShadowMapCamera> camera);
    virtual void setShadowMapZBuffers(std::array<std::shared_ptr<ZBuffer>, ShadowMapCamera::NUM> zBuffers);
    
private:
    void calculateNDCMatrix();
    Vertex getScreenVertex(const Vertex& vertex, bool &isIn); // 获取屏幕坐标的顶点
    void drawScreenTriangle(const Vertex &v0, const Vertex &v1, const Vertex &v2);

    bool isInNdcCube(const Vertex &vertex) const;
    bool isCompletelyOutsideScreen(const Vertex &v0, const Vertex &v1, const Vertex &v2);

protected:
    Eigen::Matrix4f projectionMatrix_;
    Eigen::Matrix4f ndcMatrix_; // NDC矩阵

    std::unique_ptr<BaseVS> vertexShader_; // 顶点着色器对象
    std::unique_ptr<BaseFS> fragmentShader_; // 片段着色器对象

    int width_;
    int height_;
};

#endif