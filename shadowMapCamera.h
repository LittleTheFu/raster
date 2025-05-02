#ifndef _SHADOW_MAP_CAMERA_H_
#define _SHADOW_MAP_CAMERA_H_

#include "camera.h"
#include "zbuffer.h"
#include "shadowMapVS.h"
#include "shadowMapFS.h"
#include <vector>
#include "vertexBuffer.h"

#include <Eigen/Dense>


class ShadowMapCamera
{
public:
    ShadowMapCamera(const Eigen::Vector3f& pos, const Eigen::Vector3f& target, const Eigen::Vector3f& up);
    void render(const VertexBuffer& vertexBuffer);

    Eigen::Matrix4f getViewProjectMatrix() const;
    Eigen::Matrix4f getNDCMatrix() const; // 获取NDC矩阵

    Vertex ShadowMapCamera::getScreenVertex(const Vertex &vertex) const;

    bool testZBuffer(const Eigen::Vector3f& pos) const;

private:
    void drawTriangle(const Vertex &v0, const Vertex &v1, const Vertex &v2);

private:
    const int width = 512;
    const int height = 512;

    Camera camera;
    ZBuffer zBuffer;

    ShadowMapVS vertexShader;
    ShadowMapFS fragmentShader;

    Eigen::Matrix4f ndcMatrix_; // NDC矩阵
};

#endif // _SHADOW_MAP_CAMERA_H_