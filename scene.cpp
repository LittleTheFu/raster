#include "scene.h"
#include "triangle.h"

Scene::Scene(int width, int height)
    : camera(Eigen::Vector3f(0.0f, 0.0f, -10.0f), // position
             Eigen::Vector3f(0.0f, 0.0f, 1.0f),   // target
             Eigen::Vector3f(0.0f, 1.0f, 0.0f)),  // up
      pipeline(width, height),
      mesh("teapot.obj"),
      light(Eigen::Vector3f(0.0f, 0.0f, -40.0f))
{
    const std::vector<Vertex>& vertices = mesh.getVertices();
    for (auto vertex : vertices)
    {
        vertex.worldPosition = vertex.position.head<3>(); // 世界坐标
        vertex.viewDir = (camera.position - vertex.position.head<3>()).normalized(); // 计算视线方向
        vertexBuffer.addVertex(vertex);
    }
}

std::vector<Vertex> Scene::getTriangleScreenCoords()
{
    // static int count = 0;
    // count += 1;
    // count %= 1000;

    // camera.setPosition(Eigen::Vector3f(0.0f, 0.0f, -10.0f - count * 0.01f)); // 相机位置随时间变化

    // 使用整数除法确保 count / 10 取整数部分
    // float scaleFactor = abs(sin(count * 0.0001f));
    // float scale = 1 + scaleFactor;

    std::vector<Vertex> screenCoords;

    Eigen::Matrix4f viewMatrix = camera.getViewMatrix().inverse();
    Eigen::Matrix4f projectionMatrix = camera.getProjectionMatrix();

    pipeline.setModelMatrix(Eigen::Matrix4f::Identity()); // 模型矩阵为单位矩阵
    pipeline.setViewMatrix(viewMatrix);
    pipeline.setProjectionMatrix(projectionMatrix);

    for(auto vertex : vertexBuffer.getVertices())
    {
        Vertex screenVertex = {pipeline.getScreenCoords(vertex.position),
                               vertex.color,
                               vertex.texCoord,
                               vertex.normal,
                               vertex.viewDir,
                               vertex.worldPosition};
        screenCoords.push_back(screenVertex);
    }

    return screenCoords;
}

const Light& Scene::getLight() const
{
    return light;
}