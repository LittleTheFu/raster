#ifndef _PIPELINE_H_
#define _PIPELINE_H_

#include <Eigen/Dense>

class Pipeline
{
public:
    Pipeline();

    void setModelMatrix(const Eigen::Matrix4f& modelMatrix);
    void setViewMatrix(const Eigen::Matrix4f& viewMatrix);
    void setProjectionMatrix(const Eigen::Matrix4f& projectionMatrix);

    const Eigen::Matrix4f& getMvpMatrix();

private:
    Eigen::Matrix4f modelMatrix_;
    Eigen::Matrix4f viewMatrix_;
    Eigen::Matrix4f projectionMatrix_;

    Eigen::Matrix4f mvpMatrix_; // 模型视图投影矩阵

    bool isMVPMatrixDirty_; // 是否需要更新MVP矩阵
};

#endif // _PIPELINE_H_