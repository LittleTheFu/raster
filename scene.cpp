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

std::vector<Vertex> Scene::applyVertexShader()
{
    // static int count = 0;
    // count += 1;
    // count %= 1000;

    // Corrected line (note the added closing parenthesis and proper syntax):
    // light.setPosition(Eigen::Vector3f(-100.0f + std::sin(count * 0.05f) * 200.0f,
    //                                   -100.0f + std::sin(count * 0.05f) * 200.0f,
    //                                   -40.0f));

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

    for (auto vertex : vertexBuffer.getVertices())
    {
        Vertex screenVertex = pipeline.getScreenVertex(vertex);

        screenCoords.push_back(screenVertex);
    }

    return screenCoords;
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
    static int count = 0;
    count += 1;
    count %= 1000;

    light.setPosition(Eigen::Vector3f(-100.0f + std::sin(count * 0.05f) * 200.0f,
                                      -100.0f + std::sin(count * 0.05f) * 200.0f,
                                      -40.0f));
    
    frameBuffer.clear();

    // 运行场景的渲染循环
    std::vector<Vertex> screenCoords = applyVertexShader();

    for (auto it = screenCoords.begin(); it != screenCoords.end(); it += 3)
    {
        if (it + 2 < screenCoords.end())
        {
            pipeline.drawScreenTriangle(*it, *(it + 1), *(it + 2));
        }
    }

}