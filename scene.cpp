#include "scene.h"
#include "triangle.h"

Scene::Scene(int width, int height)
    : camera(Eigen::Vector3f(0.0f, 0.0f, -30.0f), // position
             Eigen::Vector3f(0.0f, 0.0f, 1.0f),   // target
             Eigen::Vector3f(0.0f, 1.0f, 0.0f)),  // up
      mesh("teapot.obj"),
      light(Eigen::Vector3f(50.0f, 50.0f, -40.0f)),
      frameBuffer(width, height),
      shadowMapCamera(Eigen::Vector3f(50.0f, 50.0f, -40.0f), // position
                        Eigen::Vector3f(0.0f, 0.0f, 0.0f),   // target
                        Eigen::Vector3f(0.0f, 1.0f, 0.0f)),   // up
      pipeline(width, height, frameBuffer, light, shadowMapCamera)
{
    // texture = std::make_shared<Texture>("lena.png"); // 创建纹理对象
    // pipeline.setTexture(texture); // 设置纹理

    // const std::vector<Vertex> &vertices = mesh.getVertices();
    // for (auto vertex : vertices)
    // {
    //     vertex.worldPosition = vertex.position.head<3>();                            // 世界坐标
    //     vertex.viewDir = (camera.position - vertex.position.head<3>()).normalized(); // 计算视线方向
    //     vertexBuffer.addVertex(vertex);
    // }

    Vertex v0{Eigen::Vector4f(-30, -30, 60, 1),
              Eigen::Vector3f(1, 1, 1),
              Eigen::Vector2f(0, 0),
              Eigen::Vector3f(0, 0, -1),
            };
    v0.worldPosition = v0.position.head<3>(); // 世界坐标
    v0.viewDir = (camera.position - v0.position.head<3>()).normalized(); // 计算视线方向
    vertexBuffer.addVertex(v0); // 添加顶点到缓冲区

    Vertex v1{Eigen::Vector4f(-30, 30, 60, 1),
              Eigen::Vector3f(1, 1, 1),
              Eigen::Vector2f(1, 0),
              Eigen::Vector3f(0, 0, -1),
            };
    v1.worldPosition = v1.position.head<3>(); // 世界坐标
    v1.viewDir = (camera.position - v1.position.head<3>()).normalized(); // 计算视线方向
    vertexBuffer.addVertex(v1); // 添加顶点到缓冲区

    Vertex v2{Eigen::Vector4f(40, -10, 60, 1),
              Eigen::Vector3f(1, 1, 1),
              Eigen::Vector2f(0, 1),
              Eigen::Vector3f(0, 0, -1),
            };
    v2.worldPosition = v2.position.head<3>(); // 世界坐标
    v2.viewDir = (camera.position - v2.position.head<3>()).normalized(); // 计算视线方向
    vertexBuffer.addVertex(v2); // 添加顶点到缓冲区
}

const Light &Scene::getLight() const
{
    return light;
}

const FrameBuffer &Scene::getFrameBuffer() const
{
    return frameBuffer;
}

void Scene::run()
{
    // updateLightPosition(); // 更新光源位置
    shadowMapCamera.render(vertexBuffer); // 渲染阴影贴图

    frameBuffer.clear();

    Eigen::Matrix4f viewMatrix = camera.getViewMatrix().inverse();
    Eigen::Matrix4f projectionMatrix = camera.getProjectionMatrix();

    pipeline.setModelMatrix(Eigen::Matrix4f::Identity()); // 模型矩阵为单位矩阵
    pipeline.setViewMatrix(viewMatrix);
    pipeline.setProjectionMatrix(projectionMatrix);

    auto it = vertexBuffer.getVertices().begin();
    const auto end = vertexBuffer.getVertices().end();

    while (std::distance(it, end) >= 3)
    {
        Vertex v0 = pipeline.getScreenVertex(*it);
        Vertex v1 = pipeline.getScreenVertex(*(it + 1));
        Vertex v2 = pipeline.getScreenVertex(*(it + 2));

        pipeline.drawScreenTriangle(v0, v1, v2); // 绘制屏幕三角形

        std::advance(it, 3);
    }
}

void Scene::updateLightPosition()
{
    static int count = 0;
    count += 1;
    count %= 1000;

    light.setPosition(Eigen::Vector3f(-100.0f + std::sin(count * 0.05f) * 200.0f,
                                      -100.0f + std::sin(count * 0.05f) * 200.0f,
                                      -40.0f));
}
