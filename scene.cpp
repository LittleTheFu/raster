#include "scene.h"
#include "triangle.h"

Scene::Scene(int width, int height, int shadowSize)
    : camera(Eigen::Vector3f(0.0f, 0.0f, -30.0f), // position
             Eigen::Vector3f(0.0f, 0.0f, 1.0f),   // target
             Eigen::Vector3f(0.0f, 1.0f, 0.0f)),  // up
      mesh("teapot.obj"),
      frameBuffer(width, height)
{
    passG_ = std::make_unique<GPass>(width, height);
    passS_ = std::make_unique<ScreenPass>(width, height);
    passShadow_ = std::make_unique<ShadowPass>(shadowSize, shadowSize);

    light = std::make_shared<Light>(Eigen::Vector3f(2.0f, 2.0f, -2.92f));

    shadowCamera_ = std::make_shared<Camera>(
        light->getPosition(),
        Eigen::Vector3f(0, 0, 0),
        Eigen::Vector3f(0, 1, 0));

    texture = std::make_shared<Texture>("lena.png"); // 创建纹理对象
 
    const std::vector<Vertex> &vertices = mesh.getVertices();
    for (auto vertex : vertices)
    {
        vertex.worldPosition = vertex.position.head<3>();                            // 世界坐标
        vertex.viewDir = (camera.position - vertex.position.head<3>()).normalized(); // 计算视线方向
        vertexBuffer.addVertex(vertex);
    }

    Vertex v0{
        Eigen::Vector4f(-20, -20, 10, 1),
        Eigen::Vector3f(1, 1, 1),
        Eigen::Vector2f(0, 0),
        Eigen::Vector3f(0, 0, -1),
    };
    v0.worldPosition = v0.position.head<3>();                            // 世界坐标
    v0.viewDir = (camera.position - v0.position.head<3>()).normalized(); // 计算视线方向
                                                                         // 添加顶点到缓冲区

    Vertex v1{
        Eigen::Vector4f(-10, 10, 10, 1),
        Eigen::Vector3f(1, 1, 1),
        Eigen::Vector2f(1, 0),
        Eigen::Vector3f(0, 0, -1),
    };
    v1.worldPosition = v1.position.head<3>();                            // 世界坐标
    v1.viewDir = (camera.position - v1.position.head<3>()).normalized(); // 计算视线方向

    Vertex v2{
        Eigen::Vector4f(10, -10, 10, 1),
        Eigen::Vector3f(1, 1, 1),
        Eigen::Vector2f(0, 1),
        Eigen::Vector3f(0, 0, -1),
    };
    v2.worldPosition = v2.position.head<3>();                            // 世界坐标
    v2.viewDir = (camera.position - v2.position.head<3>()).normalized(); // 计算视线方向

    vertexBuffer.addVertex(v0);
    vertexBuffer.addVertex(v1);
    vertexBuffer.addVertex(v2);

    //-----------------------------------
    Vertex s0;
    s0.position = Eigen::Vector4f(-1.0f, 1.0f, 0.0f, 1.0f);
    s0.texCoord = Eigen::Vector2f(0.0f, 0.0f);
    s0.color = Eigen::Vector3f(1.0f, 1.0f, 1.0f); // 白色

    Vertex s1;
    s1.position = Eigen::Vector4f(1.0f, 1.0f, 0.0f, 1.0f);
    s1.texCoord = Eigen::Vector2f(1.0f, 0.0f);
    s1.color = Eigen::Vector3f(1.0f, 1.0f, 1.0f); // 白色

    Vertex s2;
    s2.position = Eigen::Vector4f(1.0f, -1.0f, 0.0f, 1.0f);
    s2.texCoord = Eigen::Vector2f(1.0f, 1.0f);
    s2.color = Eigen::Vector3f(1.0f, 1.0f, 1.0f); // 白色

    Vertex s3;
    s3.position = Eigen::Vector4f(-1.0f, -1.0f, 0.0f, 1.0f);
    s3.texCoord = Eigen::Vector2f(0.0f, 1.0f);
    s3.color = Eigen::Vector3f(1.0f, 1.0f, 1.0f); // 白色

    screenVertexBuffer.addVertex(s0);
    screenVertexBuffer.addVertex(s1);
    screenVertexBuffer.addVertex(s2);

    screenVertexBuffer.addVertex(s0);
    screenVertexBuffer.addVertex(s2);
    screenVertexBuffer.addVertex(s3);
}

const FrameBuffer &Scene::getFrameBuffer() const
{
    return frameBuffer;
}

const VectorBuffer &Scene::getNormalBuffer() const
{
    return passG_->getGBufferData()->normalBuffer;
}

const std::shared_ptr<ColorBuffer> &Scene::getColorBuffer() const
{
    return passS_->getColorBuffer(); // 获取颜色缓冲区
}

void Scene::run()
{
    updateLightPosition();

    frameBuffer.clear();


    Eigen::Matrix4f shadowViewMatrix = shadowCamera_->getViewMatrix().inverse();
    Eigen::Matrix4f shadowProjectionMatrix = shadowCamera_->getProjectionMatrix();
    Eigen::Matrix4f shadowMvpMatrix = shadowProjectionMatrix * shadowViewMatrix;
    passShadow_->setMvpMatrix(shadowMvpMatrix);
    passShadow_->run(vertexBuffer);

    Eigen::Matrix4f viewMatrix = camera.getViewMatrix().inverse();
    Eigen::Matrix4f projectionMatrix = camera.getProjectionMatrix();
    Eigen::Matrix4f mvpMatrix = projectionMatrix * viewMatrix; // 计算MVP矩阵
    passG_->setMvpMatrix(mvpMatrix); // 设置投影矩阵
    passG_->run(vertexBuffer);              // 执行GPass渲染通道

    //----------------------------------------------------------------------------
    Eigen::Matrix4f shadowNDCMatrix = passShadow_->getNDCMatrix();
    passS_->setShadowMapMvpMatrix(shadowMvpMatrix);
    passS_->setShadowMapNDCMatrix(shadowNDCMatrix);
    passS_->setShadowZBuffer(passShadow_->getZBuffer());

    passS_->setTexture(texture);                     // 设置纹理
    passS_->setLight(light);                         // 设置光源
    passS_->setGBufferData(passG_->getGBufferData()); // 设置GBuffer数据
    passS_->setEyePosition(camera.position);         // 设置眼睛位置
    passS_->run(screenVertexBuffer);                 // 执行屏幕渲染通道
    //----------------------------------------------------------------------------
}

void Scene::updateLightPosition()
{
    static int count = 0;
    count += 1;
    count %= 20;

    light->setPosition(Eigen::Vector3f(10.0 - (count * 0.1),
                                       0.0f - (count * 0.1),
                                       -4.0f));

    shadowCamera_->setPosition(light->getPosition());
}
