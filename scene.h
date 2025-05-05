#ifndef _SCENE_H_
#define _SCENE_H_

#include "camera.h"
#include "triangle.h"
#include "pipeline.h"
#include "vertexBuffer.h"
#include "Vertex.h"
#include "mesh.h"
#include "light.h"
#include "frameBuffer.h"
#include "texture.h"
#include <Eigen/Dense>
#include <vector>
#include "shadowMapCamera.h"

#include "GPass.h"
#include "screenPass.h"
#include "shadowPass.h"

class Scene
{
public:
    Scene(int width, int height, int shadowMapSize);

    const FrameBuffer& getFrameBuffer() const;
    const VectorBuffer& getNormalBuffer() const;
    const std::shared_ptr<ColorBuffer>& getColorBuffer() const;

    void run();

private:
    void updateLightPosition(); // 更新光源位置
    void updateCamera();

    // 计算视图矩阵和投影矩阵
    Eigen::Matrix4f getViewMatrix() const;
    Eigen::Matrix4f getProjectionMatrix() const;

private:
    std::shared_ptr<Texture> texture; // 纹理对象
    std::shared_ptr<Light> light; // 光源对象
    Camera camera;
    VertexBuffer vertexBuffer; // 顶点缓冲区
    VertexBuffer screenVertexBuffer; // 屏幕顶点缓冲区
    Mesh meshBigTeapot; // 网格对象
    Mesh meshSmallTeapot;
    FrameBuffer frameBuffer; // 帧缓冲区对象

    std::shared_ptr<ShadowMapCamera> shadowCamera_;

private:
    std::array<std::shared_ptr<ShadowPass>,ShadowMapCamera::NUM> passShadows_; // 阴影通道对象
    std::unique_ptr<GPass> passG_; // GPass对象
    std::unique_ptr<ScreenPass> passS_; // 屏幕渲染通道对象
};

#endif //_SCENE_H_