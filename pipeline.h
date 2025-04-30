#ifndef _PIPELINE_H_
#define _PIPELINE_H_

#include <Eigen/Dense>

class Pipeline
{
public:
    Pipeline(int screenWidth, int screenHeight);

    void setModelMatrix(const Eigen::Matrix4f& modelMatrix);
    void setViewMatrix(const Eigen::Matrix4f& viewMatrix);
    void setProjectionMatrix(const Eigen::Matrix4f& projectionMatrix);

    Eigen::Vector3f getScreenCoords(const Eigen::Vector4f& vertex);

private:
    const Eigen::Matrix4f& getMvpMatrix();
    void calculateNDCMatrix();

private:
    Eigen::Matrix4f modelMatrix_;
    Eigen::Matrix4f viewMatrix_;
    Eigen::Matrix4f projectionMatrix_;
    Eigen::Matrix4f ndcMatrix_; // NDC矩阵

    Eigen::Matrix4f mvpMatrix_; // 模型视图投影矩阵

    int screenWidth_; // 屏幕宽度
    int screenHeight_; // 屏幕高度

    bool isDirty_; // 是否需要更新MVP矩阵
};

#endif // _PIPELINE_H_