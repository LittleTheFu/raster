#include "scene.h"
#include "triangle.h"

Scene::Scene(int width, int height)
    : camera(Eigen::Vector3f(0.0f, 0.0f, -30.0f), // position
             Eigen::Vector3f(0.0f, 0.0f, 1.0f),   // target
             Eigen::Vector3f(0.0f, 1.0f, 0.0f)),  // up
      mesh("teapot.obj"),
      frameBuffer(width, height),
      shadowMapCamera(Eigen::Vector3f(10.0f, 20.0f, -40.0f), // position
                      Eigen::Vector3f(0.0f, 0.0f, 0.0f),     // target
                      Eigen::Vector3f(0.0f, 1.0f, 0.0f)),    // up
      passG_(width, height),
      passS_(width, height)
{
    light = std::make_shared<Light>(Eigen::Vector3f(10.0f, 20.0f, -40.0f));

    texture = std::make_shared<Texture>("lena.png"); // 创建纹理对象

    const std::vector<Vertex> &vertices = mesh.getVertices();
    for (auto vertex : vertices)
    {
        vertex.worldPosition = vertex.position.head<3>();                            // 世界坐标
        vertex.viewDir = (camera.position - vertex.position.head<3>()).normalized(); // 计算视线方向
        vertexBuffer.addVertex(vertex);
    }

    Vertex v0{
        Eigen::Vector4f(-60, -60, 60, 1),
        Eigen::Vector3f(1, 1, 1),
        Eigen::Vector2f(0, 0),
        Eigen::Vector3f(0, 0, -1),
    };
    v0.worldPosition = v0.position.head<3>();                            // 世界坐标
    v0.viewDir = (camera.position - v0.position.head<3>()).normalized(); // 计算视线方向
    vertexBuffer.addVertex(v0);                                          // 添加顶点到缓冲区

    Vertex v1{
        Eigen::Vector4f(-10, 60, 60, 1),
        Eigen::Vector3f(1, 1, 1),
        Eigen::Vector2f(1, 0),
        Eigen::Vector3f(0, 0, -1),
    };
    v1.worldPosition = v1.position.head<3>();                            // 世界坐标
    v1.viewDir = (camera.position - v1.position.head<3>()).normalized(); // 计算视线方向
    vertexBuffer.addVertex(v1);                                          // 添加顶点到缓冲区

    Vertex v2{
        Eigen::Vector4f(60, -40, 60, 1),
        Eigen::Vector3f(1, 1, 1),
        Eigen::Vector2f(0, 1),
        Eigen::Vector3f(0, 0, -1),
    };
    v2.worldPosition = v2.position.head<3>();                            // 世界坐标
    v2.viewDir = (camera.position - v2.position.head<3>()).normalized(); // 计算视线方向
    vertexBuffer.addVertex(v2);                                          // 添加顶点到缓冲区

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
    return passG_.getGBufferData()->normalBuffer;
}

const std::shared_ptr<ColorBuffer> &Scene::getColorBuffer() const
{
    return passS_.getColorBuffer(); // 获取颜色缓冲区
}

void Scene::run()
{
    frameBuffer.clear();

    Eigen::Matrix4f viewMatrix = camera.getViewMatrix().inverse();
    Eigen::Matrix4f projectionMatrix = camera.getProjectionMatrix();
    Eigen::Matrix4f mvpMatrix = projectionMatrix * viewMatrix; // 计算MVP矩阵

    passG_.setProjectionMatrix(mvpMatrix); // 设置投影矩阵
    passG_.run(vertexBuffer);              // 执行GPass渲染通道

    passS_.setLight(light); // 设置光源
    passS_.setGBufferData(passG_.getGBufferData()); // 设置GBuffer数据
    passS_.run(screenVertexBuffer); // 执行屏幕渲染通道
}

void Scene::updateLightPosition()
{
    // static int count = 0;
    // count += 1;
    // count %= 1000;

    // light.setPosition(Eigen::Vector3f(-100.0f + std::sin(count * 0.05f) * 200.0f,
    //                                   -100.0f + std::sin(count * 0.05f) * 200.0f,
    //                                   -40.0f));
}
