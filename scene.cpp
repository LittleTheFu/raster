#include "scene.h"
#include "triangle.h"

Scene::Scene(int width, int height)
    : camera(Eigen::Vector3f(0.0f, 0.0f, -10.0f), // position
             Eigen::Vector3f(0.0f, 0.0f, 1.0f),   // target
             Eigen::Vector3f(0.0f, 1.0f, 0.0f)),  // up
      mesh("teapot.obj"),
      light(Eigen::Vector3f(0.0f, 0.0f, -40.0f)),
      frameBuffer(width, height),
      pipeline(width, height, frameBuffer, light, texture),
      texture("lena.png")
{
    const std::vector<Vertex> &vertices = mesh.getVertices();
    for (auto vertex : vertices)
    {
        vertex.worldPosition = vertex.position.head<3>();                            // 世界坐标
        vertex.viewDir = (camera.position - vertex.position.head<3>()).normalized(); // 计算视线方向
        vertexBuffer.addVertex(vertex);
    }
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
    updateLightPosition(); // 更新光源位置

    frameBuffer.clear();

    Eigen::Matrix4f viewMatrix = camera.getViewMatrix().inverse();
    Eigen::Matrix4f projectionMatrix = camera.getProjectionMatrix();

    pipeline.setModelMatrix(Eigen::Matrix4f::Identity()); // 模型矩阵为单位矩阵
    pipeline.setViewMatrix(viewMatrix);
    pipeline.setProjectionMatrix(projectionMatrix);

    for (auto it = vertexBuffer.getVertices().begin(); it != vertexBuffer.getVertices().end(); it += 3)
    {
        if (it + 2 < vertexBuffer.getVertices().end())
        {
            Vertex v0 = pipeline.getScreenVertex(*it);
            Vertex v1 = pipeline.getScreenVertex(*(it + 1));
            Vertex v2 = pipeline.getScreenVertex(*(it + 2));

            pipeline.drawScreenTriangle(v0, v1, v2);
        }
    }
}

void Scene::updateLightPosition()
{
    static int count = 0;
    count += 1;
    count %= 1000;

    light.setPosition(Eigen::Vector3f(-100.0f + std::sin(count * 0.5f) * 200.0f,
                                      -100.0f + std::sin(count * 0.5f) * 200.0f,
                                      -40.0f));
}
