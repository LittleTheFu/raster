#include "scene.h"
#include "triangle.h"

Scene::Scene()
    : camera(Eigen::Vector3f(0.0f, 0.0f, -50.0f), // position
             Eigen::Vector3f(0.0f, 0.0f, 1.0f),   // target
             Eigen::Vector3f(0.0f, 1.0f, 0.0f)),  // up
      pipeline(800, 600)                          // 假设屏幕大小为800x600
{
    // 其他初始化代码
    triangle.setVertex(0, Eigen::Vector4f(0, 0, 10, 1.0f));
    triangle.setVertex(1, Eigen::Vector4f(-10, -20, 10, 1.0f));
    triangle.setVertex(2, Eigen::Vector4f(30, 10, 10, 1.0f));

    vertexBuffer.addVertex(Vertex{triangle.vertex(0), Eigen::Vector3f(1.0f, 0.0f, 0.0f)});
    vertexBuffer.addVertex(Vertex{triangle.vertex(1), Eigen::Vector3f(0.0f, 1.0f, 0.0f)});
    vertexBuffer.addVertex(Vertex{triangle.vertex(2), Eigen::Vector3f(0.0f, 0.0f, 1.0f)});
}

std::vector<Vertex> Scene::getTriangleScreenCoords()
{
    // static int count = 0;
    // count += 1;
    // count %= 1000000;

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
        Vertex screenVertex = {pipeline.getScreenCoords(vertex.position), vertex.color};
        screenCoords.push_back(screenVertex);
    }

    return screenCoords;
}