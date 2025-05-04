// #ifndef _PIPELINE_H_
// #define _PIPELINE_H_

// #include <Eigen/Dense>
// #include "vertexShader.h"
// #include "fragmentShader.h"
// #include "frameBuffer.h"
// #include "shadowMapCamera.h"

// class Pipeline
// {
// public:
//     Pipeline(int screenWidth, int screenHeight, FrameBuffer& frameBuffer, const Light& light, const ShadowMapCamera& shadowMapCamera);

//     void setTexture(const std::shared_ptr<Texture>& texture);

//     void setModelMatrix(const Eigen::Matrix4f& modelMatrix);
//     void setViewMatrix(const Eigen::Matrix4f& viewMatrix);
//     void setProjectionMatrix(const Eigen::Matrix4f& projectionMatrix);

//     Vertex getScreenVertex(const Vertex& vertex);

//     void drawScreenTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2);

// private:
//     void calculateNDCMatrix();

// private:
//     Eigen::Matrix4f modelMatrix_;
//     Eigen::Matrix4f viewMatrix_;
//     Eigen::Matrix4f projectionMatrix_;
//     Eigen::Matrix4f ndcMatrix_; // NDC矩阵

//     Eigen::Matrix4f mvpMatrix_; // 模型视图投影矩阵

//     int screenWidth_; // 屏幕宽度
//     int screenHeight_; // 屏幕高度

//     bool isDirty_; // 是否需要更新MVP矩阵

// private:
//     VertexShader vertexShader_; // 顶点着色器对象
//     FragmentShader fragmentShader_; // 片段着色器对象

//     const ShadowMapCamera& shadowMapCamera_;
// };

// #endif // _PIPELINE_H_