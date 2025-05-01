#include "scene.h"
#include "triangle.h"

Scene::Scene(int width, int height)
    : camera(Eigen::Vector3f(0.0f, 0.0f, -10.0f), // position
             Eigen::Vector3f(0.0f, 0.0f, 1.0f),   // target
             Eigen::Vector3f(0.0f, 1.0f, 0.0f)),  // up
      pipeline(width, height),
      mesh("bunny.obj")
{
    const std::vector<Vertex>& vertices = mesh.getVertices();
    for (auto vertex : vertices)
    {
        vertex.viewDir = (camera.position - vertex.position.head<3>()).normalized(); // 计算视线方向
        vertexBuffer.addVertex(vertex);
    }

    // Triangle t0;

    // // 其他初始化代码
    // t0.setVertex(0, Eigen::Vector4f(-30, 0, 10, 1.0f));
    // t0.setVertex(1, Eigen::Vector4f(10, -35, 10, 1.0f));
    // t0.setVertex(2, Eigen::Vector4f(30, 20, 10, 1.0f));

    // vertexBuffer.addVertex(Vertex{t0.vertex(0), Eigen::Vector3f(1.0f, 0.0f, 0.0f), Eigen::Vector2f(0.0f, 0.0f)});
    // vertexBuffer.addVertex(Vertex{t0.vertex(1), Eigen::Vector3f(0.0f, 1.0f, 0.0f), Eigen::Vector2f(1.0f, 0.0f)});
    // vertexBuffer.addVertex(Vertex{t0.vertex(2), Eigen::Vector3f(0.0f, 0.0f, 1.0f), Eigen::Vector2f(0.5f, 0.5f)});

    // Triangle t1;
    // t1.setVertex(0, Eigen::Vector4f(0, 0, 00, 1.0f));
    // t1.setVertex(1, Eigen::Vector4f(-10, -20, 20, 1.0f));
    // t1.setVertex(2, Eigen::Vector4f(-30, -10, 20, 1.0f));

    // vertexBuffer.addVertex(Vertex{t1.vertex(0), Eigen::Vector3f(0.0f, 1.0f, 0.0f), Eigen::Vector2f(0.0f, 0.0f)});
    // vertexBuffer.addVertex(Vertex{t1.vertex(1), Eigen::Vector3f(0.0f, 1.0f, 0.0f), Eigen::Vector2f(1.0f, 0.0f)});
    // vertexBuffer.addVertex(Vertex{t1.vertex(2), Eigen::Vector3f(0.0f, 1.0f, 0.0f), Eigen::Vector2f(0.0f, 1.0f)});
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
        Vertex screenVertex = {pipeline.getScreenCoords(vertex.position), vertex.color, vertex.texCoord, vertex.normal};
        screenCoords.push_back(screenVertex);
    }

    return screenCoords;
}